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
#include "slot_manager.hpp"

 /***
  *     .d8888b.  888          888               888
  *    d88P  Y88b 888          888               888
  *    888    888 888          888               888
  *    888        888  .d88b.  88888b.   8888b.  888
  *    888  88888 888 d88""88b 888 "88b     "88b 888
  *    888    888 888 888  888 888  888 .d888888 888
  *    Y88b  d88P 888 Y88..88P 888 d88P 888  888 888
  *     "Y8888P88 888  "Y88P"  88888P"  "Y888888 888
  *
  */

const Text_Data GlobalText::Default{};
std::unordered_set<int> GlobalText::PlayerList;
TextMap GlobalText::gText;
std::unordered_map<int, std::unordered_set<int>> GlobalText::gTextVisible;
std::unordered_map<int, int> GlobalText::realToText;

Text_Data* GlobalText::Find(int textid, const char* funcs)
{
	auto it = gText.find(textid);
	if (it == gText.end())
	{
		Plugin_Settings::ILogger(LogType::FIND_GLOBAL_TEXT, funcs, INVALID_PLAYER_ID, textid);
		return nullptr;
	}

	return &it->second;
}

void GlobalText::DestroyReal(Text_Data& data)
{
	if (data.real_id == INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		return;
	}

	TextDrawDestroy(data.real_id);
	realToText.erase(data.real_id);
	data.real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
}

bool GlobalText::Reload(int textid, Text_Data& data)
{
	if (data.real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		return true;
	}

	const int text_id = TextDrawCreate(data.create_x, data.create_y, data.text.c_str());

	if (text_id == INVALID_TEXT_DRAW)
	{
		sampgdk::logprintf("[textdraw.streamer] GlobalText::Reload: A maximum of %d global textdraws can be created.", MAX_TEXT_DRAWS);
		return false;
	}

	if (data.lettersize_x != Default.lettersize_x || data.lettersize_y != Default.lettersize_y) {
		TextDrawLetterSize(text_id, data.lettersize_x, data.lettersize_y);
	}

	if (data.textsize_x != Default.textsize_x || data.textsize_y != Default.textsize_y) {
		TextDrawTextSize(text_id, data.textsize_x, data.textsize_y);
	}

	if (data.alignment != Default.alignment) {
		TextDrawAlignment(text_id, data.alignment);
	}

	if (data.color != Default.color) {
		TextDrawColor(text_id, data.color);
	}

	if (data.usebox != Default.usebox) {
		TextDrawUseBox(text_id, data.usebox);
	}

	if (data.boxcolor != Default.boxcolor) {
		TextDrawBoxColor(text_id, data.boxcolor);
	}

	if (data.shadow != Default.shadow) {
		TextDrawSetShadow(text_id, data.shadow);
	}

	if (data.outline != Default.outline) {
		TextDrawSetOutline(text_id, data.outline);
	}

	if (data.backgroundcolor != Default.backgroundcolor) {
		TextDrawBackgroundColor(text_id, data.backgroundcolor);
	}

	if (data.font != Default.font) {
		TextDrawFont(text_id, data.font);
	}

	if (data.proportional != Default.proportional) {
		TextDrawSetProportional(text_id, data.proportional);
	}

	if (data.selectable != Default.selectable) {
		TextDrawSetSelectable(text_id, data.selectable);
	}

	if (data.font == TEXT_DRAW_FONT_MODEL_PREVIEW)
	{
		if (data.modelindex != Default.modelindex) {
			TextDrawSetPreviewModel(text_id, data.modelindex);
		}

		if (data.fRotX != Default.fRotX || data.fRotY != Default.fRotY
			|| data.fRotZ != Default.fRotZ || data.fZoom != Default.fZoom) {
			TextDrawSetPreviewRot(text_id, data.fRotX, data.fRotY, data.fRotZ, data.fZoom);
		}

		if (data.veh_col1 != Default.veh_col1 || data.veh_col2 != Default.veh_col2) {
			TextDrawSetPreviewVehCol(text_id, data.veh_col1, data.veh_col2);
		}
	}

	data.real_id = text_id;
	realToText[text_id] = textid;
	return true;
}

void GlobalText::Destroy()
{
	for (auto& entry : gText) {
		DestroyReal(entry.second);
	}

	gText.clear();
	gTextVisible.clear();
	realToText.clear();
}

 /***
  *    8888888b.  888
  *    888   Y88b 888
  *    888    888 888
  *    888   d88P 888  8888b.  888  888  .d88b.  888d888
  *    8888888P"  888     "88b 888  888 d8P  Y8b 888P"
  *    888        888 .d888888 888  888 88888888 888
  *    888        888 888  888 Y88b 888 Y8b.     888
  *    888        888 "Y888888  "Y88888  "Y8888  888
  *                                 888
  *                            Y8b d88P
  *                             "Y88P"
  */

const Text_Data PlayerText::Default{};
std::array<TextMap*, MAX_PLAYERS> PlayerText::pText{};

TextMap* PlayerText::Pool(int playerid)
{
	if (playerid < 0 || playerid >= MAX_PLAYERS) {
		return nullptr;
	}

	return pText[playerid];
}

TextMap* PlayerText::Ensure(int playerid)
{
	if (playerid < 0 || playerid >= MAX_PLAYERS) {
		return nullptr;
	}

	if (pText[playerid] == nullptr) {
		pText[playerid] = new TextMap();
	}

	return pText[playerid];
}

Text_Data* PlayerText::Find(int playerid, int textid, const char* funcs)
{
	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return nullptr;
	}

	TextMap* pool = Pool(playerid);
	if (pool == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, funcs, playerid, textid);
		return nullptr;
	}

	auto it = pool->find(textid);
	if (it == pool->end())
	{
		Plugin_Settings::ILogger(LogType::FIND_PLAYER_TEXT, funcs, playerid, textid);
		return nullptr;
	}

	return &it->second;
}

void PlayerText::DestroyReal(int playerid, Text_Data& data)
{
	if (data.real_id == INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		return;
	}

	PlayerTextDrawDestroy(playerid, data.real_id);
	data.real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
}

bool PlayerText::Reload(int playerid, Text_Data& data)
{
	if (data.real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		return true;
	}

	const int text_id = CreatePlayerTextDraw(playerid, data.create_x, data.create_y, data.text.c_str());

	// Past MAX_PLAYER_TEXT_DRAWS this comes back invalid. Storing it would leave
	// real_id at 0xFFFF, which passes every "!= INVALID" test from then on.
	if (text_id == INVALID_TEXT_DRAW) {
		return false;
	}

	if (data.lettersize_x != Default.lettersize_x || data.lettersize_y != Default.lettersize_y) {
		PlayerTextDrawLetterSize(playerid, text_id, data.lettersize_x, data.lettersize_y);
	}

	if (data.textsize_x != Default.textsize_x || data.textsize_y != Default.textsize_y) {
		PlayerTextDrawTextSize(playerid, text_id, data.textsize_x, data.textsize_y);
	}

	if (data.alignment != Default.alignment) {
		PlayerTextDrawAlignment(playerid, text_id, data.alignment);
	}

	if (data.color != Default.color) {
		PlayerTextDrawColor(playerid, text_id, data.color);
	}

	if (data.usebox != Default.usebox) {
		PlayerTextDrawUseBox(playerid, text_id, data.usebox);
	}

	if (data.boxcolor != Default.boxcolor) {
		PlayerTextDrawBoxColor(playerid, text_id, data.boxcolor);
	}

	if (data.shadow != Default.shadow) {
		PlayerTextDrawSetShadow(playerid, text_id, data.shadow);
	}

	if (data.outline != Default.outline) {
		PlayerTextDrawSetOutline(playerid, text_id, data.outline);
	}

	if (data.backgroundcolor != Default.backgroundcolor) {
		PlayerTextDrawBackgroundColor(playerid, text_id, data.backgroundcolor);
	}

	if (data.font != Default.font) {
		PlayerTextDrawFont(playerid, text_id, data.font);
	}

	if (data.proportional != Default.proportional) {
		PlayerTextDrawSetProportional(playerid, text_id, data.proportional);
	}

	if (data.selectable != Default.selectable) {
		PlayerTextDrawSetSelectable(playerid, text_id, data.selectable);
	}

	if (data.font == TEXT_DRAW_FONT_MODEL_PREVIEW)
	{
		if (data.modelindex != Default.modelindex) {
			PlayerTextDrawSetPreviewModel(playerid, text_id, data.modelindex);
		}

		if (data.fRotX != Default.fRotX || data.fRotY != Default.fRotY
			|| data.fRotZ != Default.fRotZ || data.fZoom != Default.fZoom) {
			PlayerTextDrawSetPreviewRot(playerid, text_id, data.fRotX, data.fRotY, data.fRotZ, data.fZoom);
		}

		if (data.veh_col1 != Default.veh_col1 || data.veh_col2 != Default.veh_col2) {
			PlayerTextDrawSetPreviewVehCol(playerid, text_id, data.veh_col1, data.veh_col2);
		}
	}

	data.real_id = text_id;
	return true;
}

void PlayerText::Destroy(int playerid)
{
	TextMap* pool = Pool(playerid);
	if (pool == nullptr) {
		return;
	}

	// The client drops every player textdraw on disconnect, so the server-side
	// ones do not need destroying individually here.
	delete pool;
	pText[playerid] = nullptr;

	slot_manager_player::reset_id(playerid);
}

void PlayerText::DestroyAll()
{
	for (int playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
		if (pText[playerid] == nullptr) {
			continue;
		}

		delete pText[playerid];
		pText[playerid] = nullptr;

		slot_manager_player::reset_id(playerid);
	}
}
