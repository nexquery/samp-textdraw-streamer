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

bool Plugin_Settings::logMode = true;

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	int type = params[1], textid = params[2], index	= params[3], value = params[4], playerid = params[5], ret = 0;
	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				std::map<int, int>* address = it->second->extra_id;
				(*address)[index] = value;
				ret = 1;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					std::map<int, int>* address = it->second->extra_id;
					(*address)[index] = value;
					ret = 1;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return static_cast<cell>(ret);
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	int type = params[1], textid = params[2], index = params[3], playerid = params[4], value = 0;
	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				std::map<int, int>* address = (std::map<int, int>*)it->second->extra_id;
				value = (*address)[index];
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					std::map<int, int>* address = it->second->extra_id;
					value = (*address)[index];
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return static_cast<int>(value);
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_ClearIntData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	int type = params[1], textid = params[2], playerid = params[3], ret = 0;
	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				delete it->second->extra_id;
				std::map<int, int>* address = new std::map<int, int>();
				it->second->extra_id = address;
				ret = 1;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					delete it->second->extra_id;
					std::map<int, int>* address = new std::map<int, int>();
					it->second->extra_id = address;
					ret = 1;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return static_cast<cell>(ret);
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetFloatData(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int		type		= params[1];
	int		textid		= params[2];
	float	value		= amx_ctof(params[3]);
	int		playerid	= params[4];
	int		ret			= 0;

	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				it->second->float_data = value;
				ret = 1;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					it->second->float_data = value;
					ret = 1;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetFloatData(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int		type		= params[1];
	int		textid		= params[2];
	int		playerid	= params[3];
	float	value		= 0.0;

	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				value = it->second->float_data;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					value = it->second->float_data;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return amx_ftoc(value);
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_SetArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int	type		= params[1];
	int	textid		= params[2];
	int	playerid	= params[4];
	int ret			= 0;

	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				cell* array = NULL;
				amx_GetAddr(amx, params[3], &array);
				it->second->array_data->clear();
				for (int i = 0; i < static_cast<int>(params[5]); ++i)
				{
					it->second->array_data->push_back(static_cast<int>(array[i]));
				}
				ret = 1;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					cell* array = NULL;
					amx_GetAddr(amx, params[3], &array);
					it->second->array_data->clear();
					for (int i = 0; i < static_cast<int>(params[5]); ++i)
					{
						it->second->array_data->push_back(static_cast<int>(array[i]));
					}
					ret = 1;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return static_cast<cell>(ret);
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_GetArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int	type = params[1];
	int	textid = params[2];
	int	playerid = params[4];
	int ret = 0;

	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				// Index
				int index = 0;

				// Array adresi
				cell* array = NULL;
				amx_GetAddr(amx, params[3], &array);

				// Veriyi yaz
				for (std::vector<int>::const_iterator data = it->second->array_data->begin(); data != it->second->array_data->end(); ++data)
				{
					if (index == static_cast<int>(params[5]))
					{
						break;
					}
					array[index++] = static_cast<cell>(*data);
				}

				// Basarili
				ret = 1;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					// Index
					int index = 0;

					// Array adresi
					cell* array = NULL;
					amx_GetAddr(amx, params[3], &array);

					// Veriyi yaz
					for (std::vector<int>::const_iterator data = it->second->array_data->begin(); data != it->second->array_data->end(); ++data)
					{
						if (index == static_cast<int>(params[5]))
						{
							break;
						}
						array[index++] = static_cast<cell>(*data);
					}

					// Basarili
					ret = 1;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return static_cast<cell>(ret);
}

cell AMX_NATIVE_CALL Natives::DynamicTextDraw_ClearArrayData(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int	type = params[1];
	int	textid = params[2];
	int	playerid = params[5];
	int ret = 0;

	switch (type)
	{
		case TDStreamer_Type::GLOBAL:
		{
			auto it = GlobalText::gText->find(textid);
			if (it != GlobalText::gText->end())
			{
				delete it->second->array_data;
				std::vector<int>* arr = new std::vector<int>();
				it->second->array_data = arr;
				ret = 1;
			}
			else
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, textid);
				}
			}
			break;
		}

		case TDStreamer_Type::PLAYER:
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				auto it = PlayerText::pText[playerid]->find(textid);
				if (it != PlayerText::pText[playerid]->end())
				{
					delete it->second->array_data;
					std::vector<int>* arr = new std::vector<int>();
					it->second->array_data = arr;
					ret = 1;
				}
				else
				{
					if (Plugin_Settings::logMode)
					{
						sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. TextID: %d, PlayerID: %d", __func__, textid, playerid);
					}
				}
			}
			break;
		}

		default:
		{
			if (Plugin_Settings::logMode)
			{
				sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid.", __func__);
			}
			break;
		}
	}
	return static_cast<cell>(ret);
}