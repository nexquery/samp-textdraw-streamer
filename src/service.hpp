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

#include <string>
#include <sstream>
#include "sampgdk.hpp"

namespace service
{
	void setInt(AMX* amx, cell output, int value);
	void setFloat(AMX* amx, cell output, float value);
	void setString(AMX* amx, cell output, cell size, std::string string);
	std::string getString(AMX* amx, cell input);
	std::string formattedString(AMX* amx, cell* params, cell text_index, int32_t args_offset);
};