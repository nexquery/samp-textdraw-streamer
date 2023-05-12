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

void service::setInt(AMX* amx, cell output, int value)
{
	cell* address;
	amx_GetAddr(amx, output, &address);
	*address = value;
}

void service::setFloat(AMX* amx, cell output, float value)
{
	cell* address;
	amx_GetAddr(amx, output, &address);
	*address = amx_ftoc(value);
}

void service::setString(AMX* amx, cell output, cell size, std::string string)
{
	cell* address = NULL;
	amx_GetAddr(amx, output, &address);
	amx_SetString(address, string.c_str(), 0, 0, static_cast<size_t>(size));
}

std::string service::getString(AMX* amx, cell param)
{
	cell* addr = nullptr;
	amx_GetAddr(amx, param, &addr);

	int len = 0;
	amx_StrLen(addr, &len);

	std::string string(len, ' ');
	amx_GetString(&string[0], addr, 0, len + 1);
	return string;
}

std::string service::formattedString(AMX* amx, cell* params, cell text_index, int32_t args_offset)
{
	// Argüman sayýsýný al
	int max_args = params[0] / sizeof(cell);

	// Formatlanacak metini al
	std::string metin = getString(amx, params[text_index]);

	// Argüman sayýsý offset sayýsýna ulaþýyor ve geçiyorsa formatlama aþamasýna geç
	if (max_args >= args_offset)
	{
		// Metini tarayacak index deðerimiz
		size_t index = 0;

		// Argümanýn baþlangýç offsetini ayarla
		int args_count = args_offset;

		// Döngü ile metinleri tara
		while (index < metin.length())
		{
			// Taranan metinde % karakteri var mý?
			if (metin[index] == '%')
			{
				// Varsa index deðerini +1 olarak arttýr
				index++;

				// Taranan % karakteri var mý kontrol et, varsa karakteri % olarak ayarla ve bu indexi geç
				if (metin[index] == '%')
				{
					metin[index] = '%';
					continue;
				}

				// Integer
				if (metin[index] == 'd' || metin[index] == 'i' || metin[index] == 'o' || metin[index] == 'x' || metin[index] == 'X' || metin[index] == 'u')
				{
					int yuzde = index - 1;

					cell* deger = nullptr;
					amx_GetAddr(amx, params[args_count++], &deger);

					metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<int>(*deger)));
				
					continue;
				}

				// Float
				else if (metin[index] == 'f' || metin[index] == 'F' || metin[index] == 'a' || metin[index] == 'A' || metin[index] == 'g' || metin[index] == 'G')
				{
					int yuzde = index - 1;

					cell* deger = nullptr;
					amx_GetAddr(amx, params[args_count++], &deger);

					metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<float>(amx_ctof(*deger))));

					continue;
				}

				// String
				else if (metin[index] == 's')
				{
					int yuzde = index - 1;
					metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), getString(amx, params[args_count++])));
					continue;
				}

				// Char
				else if (metin[index] == 'c')
				{
					bool degistir = false;

					int yuzde = index - 1;

					cell* deger = nullptr;
					amx_GetAddr(amx, params[args_count++], &deger);

					if (*deger == 0x25)
					{
						degistir = true;
						metin.replace(yuzde, index - yuzde + 1, "%%");
					}
					else
					{
						degistir = true;
						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<char>(*deger)));
					}

					if (degistir)
					{
						continue;
					}
				}

				// %02d, %02f vs..
				else if (metin[index] >= '0' && metin[index] <= '9')
				{
					bool degistir = false;

					int yuzde = index - 1;

					while (!isalpha(metin[index]))
					{
						index++;
					}

					if (metin[index] == 'd' || metin[index] == 'i' || metin[index] == 'o' || metin[index] == 'x' || metin[index] == 'X' || metin[index] == 'u')
					{
						cell* deger = nullptr;
						amx_GetAddr(amx, params[args_count++], &deger);

						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<int>(*deger)));
					
						degistir = true;
					}
					else if (metin[index] == 'f' || metin[index] == 'F' || metin[index] == 'a' || metin[index] == 'A' || metin[index] == 'g' || metin[index] == 'G')
					{
						cell* deger = nullptr;
						amx_GetAddr(amx, params[args_count++], &deger);

						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<float>(amx_ctof(*deger))));
					
						degistir = true;
					}

					if (degistir)
					{
						continue;
					}
				}

				// %.*s,  %.*f
				else if (metin[index] == '.' && metin[index + 1] == '*')
				{
					bool degistir = false;

					int yuzde = index - 1;

					while (!isalpha(metin[index]))
					{
						index++;
					}

					if (metin[index] == 's')
					{
						degistir = true;

						cell* deger = nullptr;
						amx_GetAddr(amx, params[args_count++], &deger);

						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<int>(*deger), getString(amx, params[args_count++])));
					}

					else if (metin[index] == 'f' || metin[index] == 'F' || metin[index] == 'a' || metin[index] == 'A' || metin[index] == 'g' || metin[index] == 'G')
					{
						degistir = true;

						cell* deger = nullptr;
						amx_GetAddr(amx, params[args_count++], &deger);

						cell* deger2 = nullptr;
						amx_GetAddr(amx, params[args_count++], &deger2);

						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<int>(*deger), static_cast<float>(amx_ctof(*deger2))));
					}

					if (degistir)
					{
						continue;
					}
				}

				// %.1s, %.1f
				else if (metin[index] == '.' && metin[index + 1] != '*')
				{
					bool degistir = false;

					int yuzde = index - 1;

					while (!isalpha(metin[index]))
					{
						index++;
					}

					if (metin[index] == 's')
					{
						degistir = true;
						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), getString(amx, params[args_count++])));
					}

					else if (metin[index] == 'f' || metin[index] == 'F' || metin[index] == 'a' || metin[index] == 'A' || metin[index] == 'g' || metin[index] == 'G')
					{
						degistir = true;

						cell* deger = nullptr;
						amx_GetAddr(amx, params[args_count++], &deger);

						metin.replace(yuzde, index - yuzde + 1, fmt::sprintf(metin.substr(yuzde, index - yuzde + 1), static_cast<float>(amx_ctof(*deger))));
					}

					if (degistir)
					{
						continue;
					}
				}
			}
			index++;
		}
	}
	return metin.c_str();
}