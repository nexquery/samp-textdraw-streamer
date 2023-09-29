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

cell AMX_NATIVE_CALL Natives::CreateDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(params[0] / sizeof(cell));

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		// Daha onceden verileri depolamak icin pointer olusturuldu mu kontrol et
		if (PlayerText::pText[playerid] == nullptr)
		{
			// Yeni bir pointer olustur
			std::unordered_map<int, Text_Data*>* pointer = new std::unordered_map<int, Text_Data*>;

			// Olusturulan pointeri kaydet
			PlayerText::pText[playerid] = pointer;
		}

		// Yeni bir kimlik al
		int auto_increment = slot_manager_player::get_id(playerid);

		// Yeni bir map haritasi olustur (Extra ID) icin
		std::map<int, int>* map = new std::map<int, int>();

		// Yeni bir vector olustur (Array) verileri icin
		std::vector<int>* arr = new std::vector<int>();

		// PlayerData verilerini olustur
		Text_Data* data = new Text_Data();
		data->real_id = -1;
		data->create_x = amx_ctof(params[2]);
		data->create_y = amx_ctof(params[3]);
		data->text = service::formattedString(amx, params, 4, 5);
		data->lettersize_x = 0.0;
		data->lettersize_y = 0.0;
		data->textsize_x = 0.0;
		data->textsize_y = 0.0;
		data->alignment = 1;
		data->color = -2;
		data->usebox = 0;
		data->boxcolor = -2;
		data->shadow = 2;
		data->outline = 0;
		data->backgroundcolor = -2;
		data->font = 1;
		data->proportional = 1;
		data->selectable = 0;
		data->modelindex = 0;
		data->fRotX = 0.0;
		data->fRotY = 0.0;
		data->fRotZ = 0.0;
		data->fZoom = 1.0;
		data->veh_col1 = -2;
		data->veh_col2 = -2;
		data->extra_id = map;
		data->float_data = 0.0;
		data->array_data = arr;

		// Veriyi pointera aktar
		PlayerText::pText[playerid]->emplace(auto_increment, data);

		return static_cast<int>(auto_increment);
	}

	return INVALID_DYNAMIC_PLAYER_TEXTDRAW;
}

//
// DestroyDynamicPlayerTextDraw(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DestroyDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		playerid = static_cast<int>(params[1]), 
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)  {
		PlayerTextDrawDestroy(playerid, it->second->real_id), it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	}

	slot_manager_player::remove_id(playerid, textid);
	delete it->second->extra_id;
	delete it->second->array_data;
	delete it->second;
	PlayerText::pText[playerid]->erase(it);
	return 1;
}

//
// DynamicPlayerTextDrawLetterSize(playerid, PlayerText:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);
	
	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);
	
	float
		width = amx_ctof(params[3]), 
		height = amx_ctof(params[4]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->lettersize_x = width;
	it->second->lettersize_y = height;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)  {
		PlayerTextDrawLetterSize(playerid, it->second->real_id, it->second->lettersize_x, it->second->lettersize_y);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawTextSize(playerid, PlayerText:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	float
		width = amx_ctof(params[3]),
		height = amx_ctof(params[4]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->textsize_x = width;
	it->second->textsize_y = height;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawTextSize(playerid, it->second->real_id, it->second->textsize_x, it->second->textsize_y);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawAlignment(playerid, PlayerText:textid, alignment, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		alignment = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->alignment = alignment;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawAlignment(playerid, it->second->real_id, it->second->alignment);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawColour(playerid, PlayerText:textid, textColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		textColour = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->color = textColour;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawColor(playerid, it->second->real_id, it->second->color);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawUseBox(playerid, PlayerText:textid, enableBox, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawUseBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		enableBox = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->usebox = enableBox;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawUseBox(playerid, it->second->real_id, it->second->usebox);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawBoxColor(playerid, PlayerText:textid, boxColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawBoxColor(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		boxColour = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->boxcolor = boxColour;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawBoxColor(playerid, it->second->real_id, it->second->boxcolor);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetShadow(playerid, PlayerText:textid, shadowSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		shadowSize = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->shadow = shadowSize;
	
	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetShadow(playerid, it->second->real_id, it->second->shadow);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetOutline(playerid, PlayerText:textid, outlineSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		outlineSize = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->outline = outlineSize;
	
	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetOutline(playerid, it->second->real_id, it->second->outline);
	}
	
	return 1;
}

//
// native DynamicPlayerTextDrawBGColour(playerid, PlayerText:textid, backgroundColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		backgroundColour = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->backgroundcolor = backgroundColour;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawBackgroundColor(playerid, it->second->real_id, it->second->backgroundcolor);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawFont(playerid, PlayerText:textid, font, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		font = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->font = font;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawFont(playerid, it->second->real_id, it->second->font);
	}

	return 1;
}

//
// native DynPlayerTextSetProportional(playerid, PlayerText:textid, proportional, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		proportional = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->proportional = proportional;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetProportional(playerid, it->second->real_id, it->second->proportional);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSelectable(playerid, PlayerText:textid, selectable, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		selectable = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->selectable = selectable;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetProportional(playerid, it->second->real_id, it->second->selectable);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawShow(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawShow(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	if (it->second->real_id == INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		int text_id = CreatePlayerTextDraw(playerid, it->second->create_x, it->second->create_y, it->second->text.c_str());
		if (text_id == INVALID_TEXT_DRAW)
		{
			Plugin_Settings::ILogger(LogType::SHOW_LIMIT_PLAYER, __func__, playerid, textid);
			return 0;
		}
		else
		{
			if (it->second->lettersize_x != PlayerText::Default.lettersize_x || it->second->lettersize_y != PlayerText::Default.lettersize_y) {
				PlayerTextDrawLetterSize(playerid, text_id, it->second->lettersize_x, it->second->lettersize_y);
			}

			if (it->second->textsize_x != PlayerText::Default.textsize_x || it->second->textsize_y != PlayerText::Default.textsize_y) {
				PlayerTextDrawTextSize(playerid, text_id, it->second->textsize_x, it->second->textsize_y);
			}

			if (it->second->alignment != PlayerText::Default.alignment) {
				PlayerTextDrawAlignment(playerid, text_id, it->second->alignment);
			}

			if (it->second->color != PlayerText::Default.color) {
				PlayerTextDrawColor(playerid, text_id, it->second->color);
			}

			if (it->second->usebox != PlayerText::Default.usebox) {
				PlayerTextDrawUseBox(playerid, text_id, it->second->usebox);
			}

			if (it->second->boxcolor != PlayerText::Default.boxcolor) {
				PlayerTextDrawBoxColor(playerid, text_id, it->second->boxcolor);
			}

			if (it->second->shadow != PlayerText::Default.shadow) {
				PlayerTextDrawSetShadow(playerid, text_id, it->second->shadow);
			}

			if (it->second->outline != PlayerText::Default.outline) {
				PlayerTextDrawSetOutline(playerid, text_id, it->second->outline);
			}

			if (it->second->backgroundcolor != PlayerText::Default.backgroundcolor) {
				PlayerTextDrawBackgroundColor(playerid, text_id, it->second->backgroundcolor);
			}

			if (it->second->font != PlayerText::Default.font) {
				PlayerTextDrawFont(playerid, text_id, it->second->font);
			}

			if (it->second->proportional != PlayerText::Default.proportional) {
				PlayerTextDrawSetProportional(playerid, text_id, it->second->proportional);
			}

			if (it->second->selectable != PlayerText::Default.selectable) {
				PlayerTextDrawSetSelectable(playerid, text_id, it->second->selectable);
			}

			if (it->second->font == TEXT_DRAW_FONT_MODEL_PREVIEW)
			{
				if (it->second->modelindex != PlayerText::Default.modelindex) {
					PlayerTextDrawSetPreviewModel(playerid, text_id, it->second->modelindex);
				}

				if (it->second->fRotX != PlayerText::Default.fRotX || it->second->fRotY != PlayerText::Default.fRotY || it->second->fRotZ != PlayerText::Default.fRotZ || it->second->fZoom != PlayerText::Default.fZoom) {
					PlayerTextDrawSetPreviewRot(playerid, text_id, it->second->fRotX, it->second->fRotY, it->second->fRotZ, it->second->fZoom);
				}

				if (it->second->veh_col1 != PlayerText::Default.veh_col1 || it->second->veh_col2 != PlayerText::Default.veh_col2) {
					PlayerTextDrawSetPreviewVehCol(playerid, text_id, it->second->veh_col1, it->second->veh_col2);
				}
			}

			it->second->real_id = text_id;
			PlayerTextDrawShow(playerid, it->second->real_id);
		}
	}
	else
	{
		PlayerTextDrawShow(playerid, it->second->real_id);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawHide(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawHide(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawDestroy(playerid, it->second->real_id), it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetString(playerid, PlayerText:textid, const format[], {Float, _}:...);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->text = service::formattedString(amx, params, 3, 4);

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetString(playerid, it->second->real_id, it->second->text.c_str());
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetPrevMdl(playerid, PlayerText:textid, model, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		model = static_cast<int>(params[3]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->modelindex = model;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetProportional(playerid, it->second->real_id, it->second->modelindex);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetPrevRot(playerid, PlayerText:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);

	int
		playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	float
		rotationX = amx_ctof(params[3]),
		rotationY = amx_ctof(params[4]),
		rotationZ = amx_ctof(params[5]),
		zoom = amx_ctof(params[6]);

	Plugin_Settings::file = service::getString(amx, params[7]);
	Plugin_Settings::line = static_cast<int>(params[8]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->fRotX = rotationX;
	it->second->fRotY = rotationY;
	it->second->fRotZ = rotationZ;
	it->second->fZoom = zoom;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetPreviewRot(playerid, it->second->real_id, it->second->fRotX, it->second->fRotY, it->second->fRotZ, it->second->fZoom);
	}
	return 1;
}

//
// native DynamicPlayerTextDrawPrevVehCol(playerid, PlayerText:textid, colour1, colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int
		playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]),
		colour1 = static_cast<int>(params[3]),
		colour2 = static_cast<int>(params[4]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->veh_col1 = colour1;
	it->second->veh_col2 = colour2;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetPreviewVehCol(playerid, it->second->real_id, it->second->veh_col1, it->second->veh_col2);
	}

	return 1;
}

//
// native IsValidDynamicPlayerTextDraw(playerid, PlayerText:textid);
//
cell AMX_NATIVE_CALL Natives::IsValidDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int
		playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr) {
		return 0;
	}

	if (PlayerText::pText[playerid]->find(textid) == PlayerText::pText[playerid]->end()) {
		return 0;
	}

	return 1;
}

//
// native IsDynamicPlayerTextDrawVisible(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::IsDynamicPlayerTextDrawVisible(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW;
}

//
// native DynamicPlayerTextDrawGetString(playerid, PlayerText:textid, string[], stringSize = sizeof(string));
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int
		playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setString(amx, params[3], params[4], it->second->text.c_str());

	return 1;
}

//
// native DynamicPlayerTextDrawSetPos(playerid, PlayerText:textid, Float:x, Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	float
		x = amx_ctof(params[3]),
		y = amx_ctof(params[4]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	it->second->create_x = x;
	it->second->create_y = y;

	if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawDestroy(playerid, it->second->real_id), it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	}

	PlayerText::Reload(playerid, it);

	return 1;
}

//
// native DynPlayerTextDrawGetLetterSize(playerid, PlayerText:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setFloat(amx, params[3], it->second->lettersize_x);
	service::setFloat(amx, params[4], it->second->lettersize_y);

	return 1;
}

//
// native DynPlayerTextDrawGetTextSize(playerid, PlayerText:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setFloat(amx, params[3], it->second->textsize_x);
	service::setFloat(amx, params[4], it->second->textsize_x);

	return 1;
}

//
// native DynamicPlayerTextDrawGetPos(playerid, PlayerText:textid, &Float:x, &Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setFloat(amx, params[3], it->second->create_x);
	service::setFloat(amx, params[4], it->second->create_y);

	return 1;
}

//
// native DynamicPlayerTextDrawGetColour(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->color);
}

//
// native DynamicPlayerTextDrawGetBoxCol(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->boxcolor);
}

//
// native DynPlayerTextDrawGetBGColour(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->backgroundcolor);
}

//
// native DynamicPlayerTextDrawGetShadow(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->shadow);
}

//
// native DynamicPlayerTextDrawGetOutline(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->outline);
}

//
// native DynamicPlayerTextDrawGetFont(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->font);
}

//
// native DynamicPlayerTextDrawIsBox(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->usebox);
}

//
// native DynPlayerTextDrawIsProportional(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->proportional);
}

//
// native DynPlayerTextDrawIsSelectable(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->selectable);
}

//
// native DynPlayerTextDrawGetAlignment(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->alignment);
}

//
// native DynPlayerTextDrawGetPreviewMdl(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[3]);
	Plugin_Settings::line = static_cast<int>(params[4]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	return static_cast<int>(it->second->modelindex);
}

//
// native DynPlayerTextDrawGetPreviewRot(playerid, PlayerText:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[7]);
	Plugin_Settings::line = static_cast<int>(params[8]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setFloat(amx, params[3], it->second->fRotX);
	service::setFloat(amx, params[4], it->second->fRotY);
	service::setFloat(amx, params[5], it->second->fRotZ);
	service::setFloat(amx, params[6], it->second->fZoom);

	return 1;
}

//
// native DynPlayerTextDrawGetPrevVehCol(playerid, PlayerText:textid, &colour1, &colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[5]);
	Plugin_Settings::line = static_cast<int>(params[6]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setInt(amx, params[3], it->second->veh_col1);
	service::setInt(amx, params[4], it->second->veh_col2);

	return 1;
}

//
// native PlayerTextDrawGetRealID(playerid, PlayerText:text, &PlayerText:realid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::PlayerTextDrawGetRealID(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	int playerid = static_cast<int>(params[1]),
		textid = static_cast<int>(params[2]);

	Plugin_Settings::file = service::getString(amx, params[4]);
	Plugin_Settings::line = static_cast<int>(params[5]);

	service::setInt(amx, params[3], INVALID_DYNAMIC_PLAYER_TEXTDRAW);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, textid);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(textid);
	if (it == PlayerText::pText[playerid]->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, __func__, playerid, textid);
		return 0;
	}

	service::setInt(amx, params[3], it->second->real_id);

	return 1;
}

cell AMX_NATIVE_CALL Natives::PlayerTextDrawGetSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);

	int playerid = static_cast<int>(params[1]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	if (PlayerText::pText[playerid] == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, 0);
		return 0;
	}

	return (PlayerText::pText[playerid]->empty()) ? (0) : (PlayerText::pText[playerid]->size());
}