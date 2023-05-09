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

#include "natives.hpp"
#include "service.hpp"
#include "slot_manager.hpp"
#include "textdraw_data.hpp"

cell AMX_NATIVE_CALL Natives::CreateDynamicTextDraw(AMX* amx, cell* params)
{
	// Parametreler
	CHECK_PARAMS(params[0] / sizeof(cell));

	// Textdraw kimliði oluþtur
	int auto_increment = slot_manager_global::get_id();

	// Extra ID oluþtur
	std::map<int, int>* map = new std::map<int, int>();

	// Array Data'yý oluþtur
	std::vector<int>* arr = new std::vector<int>();

	// Service::Native_GetString(amx, params[3]);
	// Service::FormatString(amx, params, 3);

	// Textdraw verilerini oluþtur
	Text_Data* data			= new Text_Data();
	data->real_id			= -1;
	data->create_x			= amx_ctof(params[1]);
	data->create_y			= amx_ctof(params[2]);
	data->text				= Service::Native_GetString(amx, params[3]);
	data->lettersize_x		= 0.0;
	data->lettersize_y		= 0.0;
	data->textsize_x		= 0.0;
	data->textsize_y		= 0.0;
	data->alignment			= 1;
	data->color				= -2;
	data->usebox			= 0;
	data->boxcolor			= -2;
	data->shadow			= 2;
	data->outline			= 0;
	data->backgroundcolor	= -2;
	data->font				= 1;
	data->proportional		= 1;
	data->selectable		= 0;
	data->modelindex		= 0;
	data->fRotX				= 0.0;
	data->fRotY				= 0.0;
	data->fRotZ				= 0.0;
	data->fZoom				= 1.0;
	data->veh_col1			= -2;
	data->veh_col2			= -2;
	data->extra_id			= map;
	data->float_data		= 0.0;
	data->array_data		= arr;

	// Verileri kaydet
	GlobalText::gText->emplace(auto_increment, data);
	return static_cast<cell>(auto_increment);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	int textid = static_cast<int>(params[1]);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it != GlobalText::gText->end())
	{
		// Global TextDraw
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawDestroy(it->second->real_id);
			it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
		}

		// Auto Increment
		slot_manager_global::remove_id(textid);

		// Visible
		GlobalText::gTextVisible[textid].clear();

		// Extra Id
		delete it->second->extra_id;

		// Array Data
		delete it->second->array_data;

		// Text data
		delete it->second;

		// Iterator
		GlobalText::gText->erase(it);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->lettersize_x = amx_ctof(params[2]);
		it->second->lettersize_y = amx_ctof(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawLetterSize(it->second->real_id, it->second->lettersize_x, it->second->lettersize_y);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->textsize_x = amx_ctof(params[2]);
		it->second->textsize_y = amx_ctof(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawTextSize(it->second->real_id, it->second->textsize_x, it->second->textsize_y);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->alignment = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawAlignment(it->second->real_id, it->second->alignment);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->color = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawColor(it->second->real_id, it->second->color);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawUseBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->usebox = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawUseBox(it->second->real_id, it->second->usebox);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->boxcolor = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawBoxColor(it->second->real_id, it->second->boxcolor);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->shadow = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetShadow(it->second->real_id, it->second->shadow);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->outline = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetOutline(it->second->real_id, it->second->outline);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->backgroundcolor = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawBackgroundColor(it->second->real_id, it->second->backgroundcolor);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->font = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawFont(it->second->real_id, it->second->font);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->proportional = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetProportional(it->second->real_id, it->second->proportional);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->selectable = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetSelectable(it->second->real_id, it->second->selectable);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawShowForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	int playerid = static_cast<int>(params[1]), textid = static_cast<int>(params[2]);

	// Gösterilecek oyuncu sunucuda yoksa alt fonksiyonlarý çalýþtýrma
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it != GlobalText::gText->end())
	{
		if (GlobalText::gTextVisible[textid].empty())
		{
			GlobalText::Reload(it);
			if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
			{
				GlobalText::gTextVisible[textid][playerid] = true;
				TextDrawShowForPlayer(playerid, it->second->real_id);
			}
		}
		else
		{
			GlobalText::gTextVisible[textid][playerid] = true;
			if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
			{
				TextDrawShowForPlayer(playerid, it->second->real_id);
			}
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawHideForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	int playerid = static_cast<int>(params[1]), textid = static_cast<int>(params[2]);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it != GlobalText::gText->end())
	{
		std::map<int, bool>::iterator p = GlobalText::gTextVisible[textid].find(playerid);

		if (p != GlobalText::gTextVisible[textid].end()) {
			GlobalText::gTextVisible[textid].erase(p);
		}

		if (!GlobalText::gTextVisible[textid].empty()) {
			TextDrawHideForPlayer(playerid, it->second->real_id);
		} else {
			TextDrawDestroy(it->second->real_id), it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawShowForAll(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);

	// Sunucuda bir oyuncu yoksa bu fonksiyonu çalýþtýrmayý durdur
	if (GlobalText::PlayerList.empty()) {
		return 0;
	}

	int textid = static_cast<int>(params[1]);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it != GlobalText::gText->end())
	{
		// Aktif gözüken bir kullanýcý yoksa textdrawý yeniden oluþtur
		if (GlobalText::gTextVisible[textid].empty())
		{
			// TextDraw'ý oluþtur
			GlobalText::Reload(it);
		
			// TextDraw oluþturulduysa
			if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
			{
				// Tüm oyuncularý gözüküyor olarak ayarla
				for (std::unordered_set<int>::iterator p = GlobalText::PlayerList.begin(); p != GlobalText::PlayerList.end(); p++)
				{
					GlobalText::gTextVisible[textid][*p] = true;
				}

				// TextDrawý göster
				TextDrawShowForAll(it->second->real_id);
			}
		}
		else
		{
			// Zaten gözüken oyuncu olduðu için gerçek kimlik ile tekrar göster
			TextDrawShowForAll(it->second->real_id);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawHideForAll(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	int textid = static_cast<int>(params[1]);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it != GlobalText::gText->end())
	{
		// Tüm kullanýcýlarý sýfýrla
		GlobalText::gTextVisible[textid].clear();

		// TextDraw'ý kaldýr
		TextDrawDestroy(it->second->real_id);
		it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		// Service::FormatString(amx, params, 2);
		it->second->text = Service::Native_GetString(amx, params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetString(it->second->real_id, it->second->text.c_str());
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->modelindex = static_cast<int>(params[2]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetPreviewModel(it->second->real_id, it->second->modelindex);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->fRotX = amx_ctof(params[2]);
		it->second->fRotY = amx_ctof(params[3]);
		it->second->fRotZ = amx_ctof(params[4]);
		it->second->fZoom = amx_ctof(params[5]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetPreviewRot(it->second->real_id, it->second->fRotX, it->second->fRotY, it->second->fRotZ, it->second->fZoom);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->veh_col1 = static_cast<int>(params[2]);
		it->second->veh_col2 = static_cast<int>(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawSetPreviewVehCol(it->second->real_id, it->second->veh_col1, it->second->veh_col2);
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicTextDrawVisibleForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	int playerid = static_cast<int>(params[1]), textid = static_cast<int>(params[2]);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it != GlobalText::gText->end())
	{
		std::map<int, bool>::iterator p = GlobalText::gTextVisible[textid].find(playerid);
		if (p != GlobalText::gTextVisible[textid].end())
		{
			return 1;
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetString(amx, params[2], params[3], it->second->text.c_str());
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		it->second->create_x = amx_ctof(params[2]);
		it->second->create_y = amx_ctof(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			TextDrawDestroy(it->second->real_id);
			it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
			
			GlobalText::Reload(it);
		
			for (std::unordered_set<int>::iterator p = GlobalText::PlayerList.begin(); p != GlobalText::PlayerList.end(); p++)
			{
				TextDrawShowForPlayer(*p, it->second->real_id);
			}
		}
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetFloat(amx, params[2], it->second->lettersize_x);
		Service::Native_SetFloat(amx, params[3], it->second->lettersize_y);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetFloat(amx, params[2], it->second->textsize_x);
		Service::Native_SetFloat(amx, params[3], it->second->textsize_y);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetFloat(amx, params[2], it->second->create_x);
		Service::Native_SetFloat(amx, params[3], it->second->create_y);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->color);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->boxcolor);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->backgroundcolor);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->shadow);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->outline);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->font);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->usebox);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->proportional);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->selectable);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->alignment);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		return static_cast<int>(it->second->modelindex);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetFloat(amx, params[2], it->second->fRotX);
		Service::Native_SetFloat(amx, params[3], it->second->fRotY);
		Service::Native_SetFloat(amx, params[4], it->second->fRotZ);
		Service::Native_SetFloat(amx, params[5], it->second->fZoom);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetInt(amx, params[2], it->second->veh_col1);
		Service::Native_SetInt(amx, params[3], it->second->veh_col2);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetRealID(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	if (it != GlobalText::gText->end())
	{
		Service::Native_SetInt(amx, params[2], it->second->real_id);
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item for this ID could not be found. ID: %d", __func__, static_cast<int>(params[1]));
		}
		return 0;
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetSize(AMX* amx, cell* params)
{
	return (GlobalText::gText->empty()) ? (0) : (GlobalText::gText->size());
}