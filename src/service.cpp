/*
 * Copyright (C) 2023 Burak (Nexor)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "service.hpp"
#include "fmt/printf.h"

#include <climits>
#include <vector>

bool service::setInt(AMX* amx, cell output, int value)
{
	cell* address = nullptr;
	if (amx_GetAddr(amx, output, &address) != AMX_ERR_NONE || address == nullptr) {
		return false;
	}

	*address = static_cast<cell>(value);
	return true;
}

bool service::setFloat(AMX* amx, cell output, float value)
{
	cell* address = nullptr;
	if (amx_GetAddr(amx, output, &address) != AMX_ERR_NONE || address == nullptr) {
		return false;
	}

	*address = amx_ftoc(value);
	return true;
}

bool service::setString(AMX* amx, cell output, cell size, const std::string& string)
{
	if (size <= 0) {
		return false;
	}

	cell* address = nullptr;
	if (amx_GetAddr(amx, output, &address) != AMX_ERR_NONE || address == nullptr) {
		return false;
	}

	amx_SetString(address, string.c_str(), 0, 0, static_cast<size_t>(size));
	return true;
}

std::string service::getString(AMX* amx, cell param)
{
	cell* addr = nullptr;
	if (amx_GetAddr(amx, param, &addr) != AMX_ERR_NONE || addr == nullptr) {
		return std::string();
	}

	int len = 0;
	if (amx_StrLen(addr, &len) != AMX_ERR_NONE || len <= 0) {
		return std::string();
	}

	// A separate buffer of len + 1: amx_GetString writes a terminator past the
	// last character, which must not land on a std::string's internal one.
	std::vector<char> buffer(static_cast<size_t>(len) + 1, '\0');
	if (amx_GetString(buffer.data(), addr, 0, buffer.size()) != AMX_ERR_NONE) {
		return std::string();
	}

	return std::string(buffer.data(), static_cast<size_t>(len));
}

namespace
{
	// Upper bound on a single conversion's padded output. Without this a script
	// could write "%999999999d" and force a gigabyte-sized allocation inside fmt.
	const int kMaxFieldWidth = 8192;

	// The character classification functions are UB on negative values, and this
	// plugin is routinely handed non-ASCII text.
	inline bool isDigitChar(char c)
	{
		return c >= '0' && c <= '9';
	}

	inline bool isFlagChar(char c)
	{
		return c == '-' || c == '+' || c == ' ' || c == '#' || c == '0';
	}

	// Accepted so that "%ld" is not treated as malformed, then dropped: every
	// value substituted below is already an int, a double or a string.
	inline bool isLengthChar(char c)
	{
		return c == 'h' || c == 'l' || c == 'L' || c == 'z' || c == 'j' || c == 't';
	}

	inline bool isIntConv(char c)
	{
		return c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'X' || c == 'u';
	}

	inline bool isFloatConv(char c)
	{
		return c == 'f' || c == 'F' || c == 'e' || c == 'E'
			|| c == 'g' || c == 'G' || c == 'a' || c == 'A';
	}

	// Resolves params[index], which in a Pawn variadic native is a reference.
	bool argAddress(AMX* amx, const cell* params, int index, cell** out)
	{
		if (amx_GetAddr(amx, params[index], out) != AMX_ERR_NONE || *out == nullptr) {
			return false;
		}
		return true;
	}

	struct Spec
	{
		std::string	flags;
		std::string	width;
		std::string	precision;
		bool		has_precision	= false;
		bool		star_width		= false;
		bool		star_precision	= false;
		char		conv			= '\0';
		size_t		end				= 0;	// index just past the conversion character
		bool		valid			= false;
	};

	// Parses "% [flags] [width|*] [. [precision|*]] [length] conversion" starting
	// at the '%' in format[start]. Never reads past format.size().
	Spec parseSpec(const std::string& format, size_t start)
	{
		Spec spec;
		const size_t n = format.size();
		size_t i = start + 1;

		while (i < n && isFlagChar(format[i])) {
			spec.flags.push_back(format[i++]);
		}

		if (i < n && format[i] == '*') {
			spec.star_width = true;
			++i;
		}
		else {
			while (i < n && isDigitChar(format[i])) {
				spec.width.push_back(format[i++]);
			}
		}

		if (i < n && format[i] == '.') {
			spec.has_precision = true;
			++i;

			if (i < n && format[i] == '*') {
				spec.star_precision = true;
				++i;
			}
			else {
				while (i < n && isDigitChar(format[i])) {
					spec.precision.push_back(format[i++]);
				}
			}
		}

		while (i < n && isLengthChar(format[i])) {
			++i;
		}

		if (i >= n) {
			spec.end = n;
			return spec;
		}

		spec.conv = format[i];
		spec.end = i + 1;
		spec.valid = isIntConv(spec.conv) || isFloatConv(spec.conv)
			|| spec.conv == 's' || spec.conv == 'c';

		return spec;
	}

	// Parses a numeric field, clamping to kMaxFieldWidth. Returns an empty string
	// for anything unparseable or non-positive, which drops the field entirely.
	std::string clampField(const std::string& digits)
	{
		if (digits.empty()) {
			return std::string();
		}

		long value = 0;
		for (size_t i = 0; i < digits.size(); ++i)
		{
			value = value * 10 + (digits[i] - '0');
			if (value > kMaxFieldWidth) {
				return std::to_string(kMaxFieldWidth);
			}
		}

		return std::to_string(value);
	}

	// Rebuilds the specifier with any '*' already resolved to a literal number,
	// so the value below is the only argument fmt has to bind.
	std::string buildSpec(const Spec& spec, char conv)
	{
		std::string out("%");
		out += spec.flags;
		out += clampField(spec.width);

		if (spec.has_precision) {
			const std::string precision = clampField(spec.precision);
			out += '.';
			out += precision.empty() ? std::string("0") : precision;
		}

		out += conv;
		return out;
	}
}

std::string service::formattedString(AMX* amx, const cell* params, cell text_index, int args_offset)
{
	const std::string format = getString(amx, params[text_index]);

	// Number of cells the script actually passed.
	const int max_args = static_cast<int>(params[0] / sizeof(cell));

	std::string out;
	out.reserve(format.size() + 32);

	const size_t n = format.size();
	int arg = args_offset;
	size_t i = 0;

	while (i < n)
	{
		if (format[i] != '%') {
			out.push_back(format[i++]);
			continue;
		}

		// "%%" is a literal percent sign.
		if (i + 1 < n && format[i + 1] == '%') {
			out.push_back('%');
			i += 2;
			continue;
		}

		const Spec spec = parseSpec(format, i);

		// A '*' width and a '*' precision each consume an argument of their own,
		// on top of the value itself.
		const int needed = 1
			+ (spec.star_width ? 1 : 0)
			+ (spec.star_precision ? 1 : 0);

		// Anything unparseable, or not backed by enough arguments, is emitted
		// exactly as it was written rather than scanned past.
		if (!spec.valid || arg + needed - 1 > max_args) {
			out.append(format, i, spec.end - i);
			i = spec.end;
			continue;
		}

		Spec resolved = spec;
		bool failed = false;

		if (resolved.star_width) {
			cell* address = nullptr;
			if (argAddress(amx, params, arg++, &address))
			{
				// A negative '*' width means left-align by that many columns,
				// which is the '-' flag plus a positive width.
				int width = static_cast<int>(*address);
				if (width < 0)
				{
					resolved.flags += '-';
					width = (width == INT_MIN) ? kMaxFieldWidth : -width;
				}

				resolved.width = std::to_string(width);
			}
			else {
				failed = true;
			}
		}

		if (!failed && resolved.star_precision) {
			cell* address = nullptr;
			if (argAddress(amx, params, arg++, &address))
			{
				// A negative '*' precision is specified to behave as if omitted.
				const int precision = static_cast<int>(*address);
				if (precision < 0) {
					resolved.has_precision = false;
				}
				else {
					resolved.precision = std::to_string(precision);
				}
			}
			else {
				failed = true;
			}
		}

		if (!failed)
		{
			// fmt throws on a specifier it cannot bind; a bad format string from a
			// script must not be able to take the server down.
			try
			{
				if (resolved.conv == 's')
				{
					out += fmt::sprintf(buildSpec(resolved, 's'), getString(amx, params[arg++]));
				}
				else if (resolved.conv == 'c')
				{
					cell* address = nullptr;
					if (argAddress(amx, params, arg++, &address)) {
						out += fmt::sprintf(buildSpec(resolved, 'c'), static_cast<char>(*address));
					}
					else {
						failed = true;
					}
				}
				else if (isFloatConv(resolved.conv))
				{
					cell* address = nullptr;
					if (argAddress(amx, params, arg++, &address)) {
						out += fmt::sprintf(buildSpec(resolved, resolved.conv),
							static_cast<double>(amx_ctof(*address)));
					}
					else {
						failed = true;
					}
				}
				else	// integer conversions
				{
					cell* address = nullptr;
					if (argAddress(amx, params, arg++, &address))
					{
						if (resolved.conv == 'u' || resolved.conv == 'o'
							|| resolved.conv == 'x' || resolved.conv == 'X')
						{
							out += fmt::sprintf(buildSpec(resolved, resolved.conv),
								static_cast<unsigned int>(*address));
						}
						else
						{
							out += fmt::sprintf(buildSpec(resolved, resolved.conv),
								static_cast<int>(*address));
						}
					}
					else {
						failed = true;
					}
				}
			}
			catch (...)
			{
				failed = true;
			}
		}

		if (failed) {
			out.append(format, i, spec.end - i);
		}

		i = spec.end;
	}

	return out;
}
