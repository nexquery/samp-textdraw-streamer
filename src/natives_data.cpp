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

 //
 // native DynamicTextDraw_SetIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, index, value, playerid = -1);
 //
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	
	int
		type		= params[1],
		textid		= params[2],
		index		= params[3],
		value		= params[4],
		playerid	= params[5];
	
	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		std::map<int, int>* address = it->second->extra_id;
		(*address)[index] = value;
		return 1;
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}

			std::map<int, int>* address = it->second->extra_id;
			(*address)[index] = value;
			return 1;
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}

	return 0;
}

//
// native DynamicTextDraw_GetIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, index, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	
	int
		type		= params[1],
		textid		= params[2],
		index		= params[3],
		playerid	= params[4];
	
	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		std::map<int, int>* address = (std::map<int, int>*)it->second->extra_id;
		return (*address)[index];
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}

			std::map<int, int>* address = it->second->extra_id;
			return (*address)[index];
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}

	return 0;
}

//
// native DynamicTextDraw_ClearIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_ClearIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	
	int
		type		= params[1],
		textid		= params[2],
		playerid	= params[3];

	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		delete it->second->extra_id;
		std::map<int, int>* address = new std::map<int, int>();
		it->second->extra_id = address;
		return 1;
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}

			delete it->second->extra_id;
			std::map<int, int>* address = new std::map<int, int>();
			it->second->extra_id = address;
			return 1;
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}

	return 0;
}

//
// native DynamicTextDraw_SetFloatData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, Float:value, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetFloatData(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int		type		= params[1];
	int		textid		= params[2];
	float	value		= amx_ctof(params[3]);
	int		playerid	= params[4];

	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		it->second->float_data = value;
		return 1;
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}

			it->second->float_data = value;
			return 1;
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}

	return 0;
}

//
// native Float:DynamicTextDraw_GetFloatData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetFloatData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int		type		= params[1];
	int		textid		= params[2];
	int		playerid	= params[3];
	float	value		= 0.0;

	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return amx_ftoc(value);
		}
		return amx_ftoc(it->second->float_data);
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return amx_ftoc(value);
			}
			return amx_ftoc(it->second->float_data);
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}
	return amx_ftoc(value);
}

//
// native DynamicTextDraw_SetArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, const src[], playerid = -1, maxSrc = sizeof(src));
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int	type		= params[1];
	int	textid		= params[2];
	int	playerid	= params[4];

	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		it->second->array_data->clear();

		cell* array = NULL;
		amx_GetAddr(amx, params[3], &array);
		for (int i = 0, j = static_cast<int>(params[5]); i != j; ++i)
		{
			it->second->array_data->push_back(static_cast<int>(array[i]));
		}
		return 1;
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}
			
			it->second->array_data->clear();

			cell* array = NULL;
			amx_GetAddr(amx, params[3], &array);
			for (int i = 0, j = static_cast<int>(params[5]); i != j; ++i)
			{
				it->second->array_data->push_back(static_cast<int>(array[i]));
			}
			return 1;
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}
	return 0;
}

//
// native DynamicTextDraw_GetArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, const dest[], playerid = -1, maxDest = sizeof(dest));
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int	type = params[1];
	int	textid = params[2];
	int	playerid = params[4];

	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		int index = 0;
		cell* array = NULL;
		amx_GetAddr(amx, params[3], &array);

		for (std::vector<int>::const_iterator data = it->second->array_data->begin(); data != it->second->array_data->end(); ++data)
		{
			if (index == static_cast<int>(params[5]))
			{
				break;
			}
			array[index++] = static_cast<cell>(*data);
		}
		return 1;
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}

			int index = 0;
			cell* array = NULL;
			amx_GetAddr(amx, params[3], &array);

			for (std::vector<int>::const_iterator data = it->second->array_data->begin(); data != it->second->array_data->end(); ++data)
			{
				if (index == static_cast<int>(params[5]))
				{
					break;
				}
				array[index++] = static_cast<cell>(*data);
			}
			return 1;
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}
	return 0;
}

//
// native DynamicTextDraw_ClearArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDraw_ClearArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int	type = params[1];
	int	textid = params[2];
	int	playerid = params[3];

	if (type == TDStreamer_Type::GLOBAL)
	{
		auto it = GlobalText::gText->find(textid);
		if (it == GlobalText::gText->end())
		{
			Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		delete it->second->array_data;
		std::vector<int>* arr = new std::vector<int>();
		it->second->array_data = arr;
		return 1;
	}
	else if (type == TDStreamer_Type::PLAYER)
	{
		if (playerid >= 0 && playerid < MAX_PLAYERS)
		{
			auto it = PlayerText::pText[playerid]->find(textid);
			if (it == PlayerText::pText[playerid]->end())
			{
				Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
				return 0;
			}

			delete it->second->array_data;
			std::vector<int>* arr = new std::vector<int>();
			it->second->array_data = arr;
			return 1;
		}
	}
	else
	{
		Plugin_Settings::ILogger(LogType::INVALID_TYPE, __func__, INVALID_PLAYER_ID, INVALID_PLAYER_ID);
	}
	return 0;
}