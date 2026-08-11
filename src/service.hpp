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

#pragma once

#include <string>
#include "sampgdk.hpp"

namespace service
{
	// Each of these returns false when the AMX address cannot be resolved,
	// rather than writing through an unresolved pointer.
	bool setInt(AMX* amx, cell output, int value);
	bool setFloat(AMX* amx, cell output, float value);
	bool setString(AMX* amx, cell output, cell size, const std::string& string);

	// Returns an empty string when the address cannot be resolved.
	std::string getString(AMX* amx, cell input);

	// printf-style substitution of the AMX arguments starting at args_offset into
	// the format string at text_index. A malformed format is emitted verbatim: it
	// never reads past the end of the format or past params[params[0] / sizeof(cell)].
	std::string formattedString(AMX* amx, const cell* params, cell text_index, int args_offset);
};
