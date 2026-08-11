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

#include "textdraw_data.hpp"
#include "natives.hpp"
#include "service.hpp"

#include <algorithm>

namespace
{
	// Resolves either flavour of textdraw behind the type discriminator.
	//
	// The player branch previously did PlayerText::pText[playerid]->find(...) with
	// no null check, which segfaulted the server for any player who had not yet
	// created a player textdraw. PlayerText::Find performs the same guard sequence
	// and logging as every other player native.
	Text_Data* resolve(int type, int textid, int playerid, const char* funcs)
	{
		if (type == TDStreamer_Type::GLOBAL) {
			return GlobalText::Find(textid, funcs);
		}

		if (type == TDStreamer_Type::PLAYER) {
			return PlayerText::Find(playerid, textid, funcs);
		}

		Plugin_Settings::ILogger(LogType::INVALID_TYPE, funcs, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
		return nullptr;
	}
}

 //
 // native DynamicTextDraw_SetIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, index, value, playerid = -1);
 //
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[5]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	data->extra_id[static_cast<int>(params[3])] = static_cast<int>(params[4]);
	return 1;
}

//
// native DynamicTextDraw_GetIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, index, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[4]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	// Deliberately does not insert on a miss, unlike the operator[] this replaces.
	auto it = data->extra_id.find(static_cast<int>(params[3]));
	return (it == data->extra_id.end()) ? 0 : static_cast<cell>(it->second);
}

//
// native DynamicTextDraw_ClearIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_ClearIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[3]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	data->extra_id.clear();
	return 1;
}

//
// native DynamicTextDraw_SetFloatData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, Float:value, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetFloatData(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[4]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	data->float_data = amx_ctof(params[3]);
	return 1;
}

//
// native Float:DynamicTextDraw_GetFloatData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetFloatData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[3]),
		__func__);

	float value = 0.0f;
	if (data != nullptr) {
		value = data->float_data;
	}

	return amx_ftoc(value);
}

//
// native DynamicTextDraw_SetArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, const src[], playerid = -1, maxSrc = sizeof(src));
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[4]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	const int count = static_cast<int>(params[5]);
	if (count <= 0) {
		data->array_data.clear();
		return 1;
	}

	cell* array = nullptr;
	if (amx_GetAddr(amx, params[3], &array) != AMX_ERR_NONE || array == nullptr) {
		return 0;
	}

	data->array_data.assign(array, array + count);
	return 1;
}

//
// native DynamicTextDraw_GetArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, const dest[], playerid = -1, maxDest = sizeof(dest));
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[4]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	const int capacity = static_cast<int>(params[5]);
	if (capacity <= 0) {
		return 0;
	}

	cell* array = nullptr;
	if (amx_GetAddr(amx, params[3], &array) != AMX_ERR_NONE || array == nullptr) {
		return 0;
	}

	const size_t limit = (std::min)(static_cast<size_t>(capacity), data->array_data.size());
	for (size_t i = 0; i < limit; ++i) {
		array[i] = static_cast<cell>(data->array_data[i]);
	}

	return 1;
}

//
// native DynamicTextDraw_ClearArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_ClearArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Text_Data* data = resolve(
		static_cast<int>(params[1]),
		static_cast<int>(params[2]),
		static_cast<int>(params[3]),
		__func__);

	if (data == nullptr) {
		return 0;
	}

	data->array_data.clear();
	return 1;
}
