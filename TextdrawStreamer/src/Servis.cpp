/*
 * Copyright (C) 2020 Burak (NexoR)
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

#include "Servis.h"

std::string Servis::Get_String(AMX* amx, cell params)
{
	int len;
	cell* adres;
	amx_GetAddr(amx, params, &adres);
	amx_StrLen(adres, &len);
	char* sz = new char[len + 1];
	amx_GetString(sz, adres, 0, len + 1);
	std::string str = sz;
	delete[] sz;
	return str;
}