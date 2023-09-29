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

 //
 // native Text:CreateDynamicTextDraw(Float:x, Float:y, const format[], {Float, _}:...);
 //
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

	// Textdraw verilerini oluþtur
	Text_Data* data			= new Text_Data();
	data->real_id			= -1;
	data->create_x			= amx_ctof(params[1]);
	data->create_y			= amx_ctof(params[2]);
	data->text				= service::formattedString(amx, params, 3, 4);
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

//
// native DestroyDynamicTextDraw(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DestroyDynamicTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	
	int 
		textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) 
	{
		TextDrawDestroy(it->second->real_id), it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
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
	return 1;
}

//
// native DynamicTextDrawLetterSize(Text:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int 
		textid = static_cast<int>(params[1]);

	float
		width = amx_ctof(params[2]),
		height = amx_ctof(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->lettersize_x = width;
	it->second->lettersize_y = height;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawLetterSize(it->second->real_id, it->second->lettersize_x, it->second->lettersize_y);
	}

	return 1;
}

//
// native DynamicTextDrawTextSize(Text:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int
		textid = static_cast<int>(params[1]);

	float
		width = amx_ctof(params[2]),
		height = amx_ctof(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->textsize_x = width;
	it->second->textsize_y = height;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawTextSize(it->second->real_id, it->second->textsize_x, it->second->textsize_y);
	}

	return 1;
}

//
// native DynamicTextDrawAlignment(Text:textid, alignment, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		alignment = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->alignment = static_cast<int>(params[2]);

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawAlignment(it->second->real_id, it->second->alignment);
	}

	return 1;
}

//
// native DynamicTextDrawColour(Text:textid, textColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		textColour = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->color = textColour;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawColor(it->second->real_id, it->second->color);
	}

	return 1;
}

//
// native DynamicTextDrawUseBox(Text:textid, enableBox, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawUseBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		enableBox = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->usebox = enableBox;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawUseBox(it->second->real_id, it->second->usebox);
	}

	return 1;
}

//
// native DynamicTextDrawBoxColour(Text:textid, boxColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		boxColour = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->boxcolor = boxColour;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawBoxColor(it->second->real_id, it->second->boxcolor);
	}
	
	return 1;
}

//
// native DynamicTextDrawSetShadow(Text:textid, shadowSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		shadowSize = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->shadow = shadowSize;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetShadow(it->second->real_id, it->second->shadow);
	}

	return 1;
}

//
// native DynamicTextDrawSetOutline(Text:textid, outlineSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		outlineSize = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->outline = outlineSize;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetOutline(it->second->real_id, it->second->outline);
	}

	return 1;
}

//
// native DynamicTextDrawBackgroundColour(Text:textid, backgroundColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		backgroundColour = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->backgroundcolor = backgroundColour;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawBackgroundColor(it->second->real_id, it->second->backgroundcolor);
	}

	return 1;
}

//
// native DynamicTextDrawFont(Text:textid, font, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		font = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->font = font;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawFont(it->second->real_id, it->second->font);
	}

	return 1;
}

//
// native DynamicTextDrawSetProportional(Text:textid, proportional, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		proportional = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->proportional = proportional;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetProportional(it->second->real_id, it->second->proportional);
	}

	return 1;
}

//
// native DynamicTextDrawSetSelectable(Text:textid, selectable, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		selectable = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->selectable = selectable;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetSelectable(it->second->real_id, it->second->selectable);
	}

	return 1;
}

//
// native DynamicTextDrawShowForPlayer(playerid, Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawShowForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	
	int 
		playerid = static_cast<int>(params[1]), 
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	// Gösterilecek oyuncu sunucuda yoksa alt fonksiyonlarý çalýþtýrma
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

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

	return 1;
}

//
// native DynamicTextDrawHideForPlayer(playerid, Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawHideForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	
	int 
		playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	std::map<int, bool>::iterator p = GlobalText::gTextVisible[textid].find(playerid);

	if (p != GlobalText::gTextVisible[textid].end()) {
		GlobalText::gTextVisible[textid].erase(p);
	}

	if (!GlobalText::gTextVisible[textid].empty())
	{
		TextDrawHideForPlayer(playerid, it->second->real_id);
	}
	else
	{
		TextDrawDestroy(it->second->real_id), it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	}

	return 1;
}

//
// native DynamicTextDrawShowForAll(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawShowForAll(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	// Sunucuda bir oyuncu yoksa bu fonksiyonu çalýþtýrmayý durdur
	if (GlobalText::PlayerList.empty()) {
		return 0;
	}

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

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

	return 1;
}

//
// native DynamicTextDrawHideForAll(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawHideForAll(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);
	
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}
	
	// Tüm kullanýcýlarý sýfýrla
	GlobalText::gTextVisible[textid].clear();

	// TextDraw'ý kaldýr
	TextDrawDestroy(it->second->real_id);
	it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;

	return 1;
}

//
// native DynamicTextDrawSetString(Text:textid, const format[], {Float, _}:...);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	int textid = static_cast<int>(params[1]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->text = service::formattedString(amx, params, 2, 3);

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetString(it->second->real_id, it->second->text.c_str());
	}

	return 1;
}

//
// native DynamicTextDrawSetPreviewModel(Text:textid, model, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		textid = static_cast<int>(params[1]),
		model = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->modelindex = model;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetPreviewModel(it->second->real_id, it->second->modelindex);
	}

	return 1;
}

//
// native DynamicTextDrawSetPreviewRot(Text:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(7);

	int
		textid = static_cast<int>(params[1]);

	float
		rotationX	= amx_ctof(params[2]),
		rotationY	= amx_ctof(params[3]),
		rotationZ	= amx_ctof(params[4]),
		zoom		= amx_ctof(params[5]);

	Plugin_Settings::file = service::getString(amx, params[6]);
	Plugin_Settings::line = static_cast<int>(params[7]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->fRotX = rotationX;
	it->second->fRotY = rotationY;
	it->second->fRotZ = rotationZ;
	it->second->fZoom = zoom;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetPreviewRot(it->second->real_id, it->second->fRotX, it->second->fRotY, it->second->fRotZ, it->second->fZoom);
	}

	return 1;
}

//
// native DynamicTextDrawSetPreviewVehCol(Text:textid, colour1, colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int
		textid = static_cast<int>(params[1]),
		colour1 = static_cast<int>(params[2]),
		colour2 = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->veh_col1 = colour1;
	it->second->veh_col2 = colour2;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		TextDrawSetPreviewVehCol(it->second->real_id, it->second->veh_col1, it->second->veh_col2);
	}

	return 1;
}

//
// native IsValidDynamicTextDraw(Text:textid);
//
cell AMX_NATIVE_CALL Natives::IsValidDynamicTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(static_cast<int>(params[1]));
	return it != GlobalText::gText->end();
}

//
// native IsDynTextDrawVisibleForPlayer(playerid, Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::IsDynamicTextDrawVisibleForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	
	int 
		playerid = static_cast<int>(params[1]), 
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	std::map<int, bool>::iterator p = GlobalText::gTextVisible[textid].find(playerid);
	if (p == GlobalText::gTextVisible[textid].end())
	{
		return 0;
	}

	return 1;
}

//
// native DynamicTextDrawGetString(Text:textid, string[], stringSize = sizeof(string));
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	service::setString(amx, params[2], params[3], it->second->text.c_str());
	return 1;
}

//
// native DynamicTextDrawSetPos(Text:textid, Float:x, Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int
		textid = static_cast<int>(params[1]);

	float
		x = amx_ctof(params[2]),
		y = amx_ctof(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	it->second->create_x = x;
	it->second->create_y = y;

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

	return 1;
}

//
// native DynamicTextDrawGetLetterSize(Text:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	service::setFloat(amx, params[2], it->second->lettersize_x);
	service::setFloat(amx, params[3], it->second->lettersize_y);

	return 1;
}

//
// native DynamicTextDrawGetTextSize(Text:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	service::setFloat(amx, params[2], it->second->textsize_x);
	service::setFloat(amx, params[3], it->second->textsize_y);

	return 1;
}

//
// native DynamicTextDrawGetPos(Text:textid, &Float:x, &Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	service::setFloat(amx, params[2], it->second->create_x);
	service::setFloat(amx, params[3], it->second->create_y);

	return 1;
}

//
// native DynamicTextDrawGetColour(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->color);
}

//
// native DynamicTextDrawGetBoxColour(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->boxcolor);
}

//
// native DynamicTextDrawGetBackgroundCol(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->backgroundcolor);
}

//
// native DynamicTextDrawGetShadow(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->shadow);
}

//
// native DynamicTextDrawGetOutline(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->outline);
}

//
// native DynamicTextDrawGetFont(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->font);
}

//
// native DynamicTextDrawIsBox(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->usebox);
}

//
// native DynamicTextDrawIsProportional(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->proportional);
}

//
// native DynamicTextDrawIsSelectable(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->selectable);
}

//
// native DynamicTextDrawGetAlignment(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->alignment);
}

//
// native DynamicTextDrawGetPreviewModel(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[2]);
	Plugin_Settings::line = static_cast<int>(params[3]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	return static_cast<int>(it->second->modelindex);
}

//
// native DynamicTextDrawGetPreviewRot(Text:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(7);
	
	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[6]);
	Plugin_Settings::line = static_cast<int>(params[7]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}
	
	service::setFloat(amx, params[2], it->second->fRotX);
	service::setFloat(amx, params[3], it->second->fRotY);
	service::setFloat(amx, params[4], it->second->fRotZ);
	service::setFloat(amx, params[5], it->second->fZoom);

	return 1;
}

//
// native DynamicTextDrawGetPreviewVehCo(Text:textid, &colour1, &colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	service::setInt(amx, params[2], it->second->veh_col1);
	service::setInt(amx, params[3], it->second->veh_col2);

	return 1;
}

//
// native DynamicTextDrawGetRealID(Text:textid, &Text:realid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetRealID(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int textid = static_cast<int>(params[1]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	service::setInt(amx, params[2], INVALID_DYNAMIC_PLAYER_TEXTDRAW);

	std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->find(textid);
	if (it == GlobalText::gText->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	service::setInt(amx, params[2], it->second->real_id);

	return 1;
}

cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetSize(AMX* amx, cell* params)
{
	return (GlobalText::gText->empty()) ? (0) : (GlobalText::gText->size());
}