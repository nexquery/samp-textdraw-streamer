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
#include "sampgdk.hpp"


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
  *
  *
  */

DefaultText GlobalText::Default;
std::unordered_set<int> GlobalText::PlayerList;
std::unordered_map<int, Text_Data*>* GlobalText::gText = new std::unordered_map<int, Text_Data*>();
std::map<int, std::map<int, bool>> GlobalText::gTextVisible;

void GlobalText::Destroy()
{
	if (!gText->empty())
	{
		for (auto it = gText->begin(); it != gText->end(); it++)
		{
			// Extra id
			delete it->second->extra_id;
			
			// Array data
			delete it->second->array_data;
			
			// Text data
			delete it->second;
		}

		delete gText;
		gText = nullptr;
	}
}

void GlobalText::Reload(std::unordered_map<int, Text_Data*>::iterator it)
{
	if (it->second->real_id == INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		int text_id = TextDrawCreate(it->second->create_x, it->second->create_y, it->second->text.c_str());

		if (text_id == INVALID_TEXT_DRAW)
		{
			sampgdk::logprintf("[textdraw.streamer] GlobalText::Reload: A maximum of %d global textdraws can be created.", MAX_TEXT_DRAWS);
			return;
		}

		if (it->second->lettersize_x != GlobalText::Default.lettersize_x || it->second->lettersize_y != GlobalText::Default.lettersize_y) {
			TextDrawLetterSize(text_id, it->second->lettersize_x, it->second->lettersize_y);
		}

		if (it->second->textsize_x != GlobalText::Default.textsize_x || it->second->textsize_y != GlobalText::Default.textsize_y) {
			TextDrawTextSize(text_id, it->second->textsize_x, it->second->textsize_y);
		}

		if (it->second->alignment != GlobalText::Default.alignment) {
			TextDrawAlignment(text_id, it->second->alignment);
		}

		if (it->second->color != GlobalText::Default.color) {
			TextDrawColor(text_id, it->second->color);
		}

		if (it->second->usebox != GlobalText::Default.usebox) {
			TextDrawUseBox(text_id, it->second->usebox);
		}

		if (it->second->boxcolor != GlobalText::Default.boxcolor) {
			TextDrawBoxColor(text_id, it->second->boxcolor);
		}

		if (it->second->shadow != GlobalText::Default.shadow) {
			TextDrawSetShadow(text_id, it->second->shadow);
		}

		if (it->second->outline != GlobalText::Default.outline) {
			TextDrawSetOutline(text_id, it->second->outline);
		}

		if (it->second->backgroundcolor != GlobalText::Default.backgroundcolor) {
			TextDrawBackgroundColor(text_id, it->second->backgroundcolor);
		}

		if (it->second->font != GlobalText::Default.font) {
			TextDrawFont(text_id, it->second->font);
		}

		if (it->second->proportional != GlobalText::Default.proportional) {
			TextDrawSetProportional(text_id, it->second->proportional);
		}

		if (it->second->selectable != GlobalText::Default.selectable) {
			TextDrawSetSelectable(text_id, it->second->selectable);
		}

		if (it->second->font == TEXT_DRAW_FONT_MODEL_PREVIEW)
		{
			if (it->second->modelindex != GlobalText::Default.modelindex) {
				TextDrawSetPreviewModel(text_id, it->second->modelindex);
			}

			if (it->second->fRotX != GlobalText::Default.fRotX || it->second->fRotY != GlobalText::Default.fRotY || it->second->fRotZ != GlobalText::Default.fRotZ || it->second->fZoom != GlobalText::Default.fZoom) {
				TextDrawSetPreviewRot(text_id, it->second->fRotX, it->second->fRotY, it->second->fRotZ, it->second->fZoom);
			}

			if (it->second->veh_col1 != GlobalText::Default.veh_col1 || it->second->veh_col2 != GlobalText::Default.veh_col2) {
				TextDrawSetPreviewVehCol( text_id, it->second->veh_col1, it->second->veh_col2);
			}
		}

		it->second->real_id = text_id;
	}
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

DefaultText PlayerText::Default;
std::unordered_map<int, std::unordered_map<int, Text_Data*>*> PlayerText::pText;

void PlayerText::Destroy(int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		// Eger veri yoksa alt islemleri calistirma
		if (pText[playerid] == nullptr) {
			return;
		}

		// Sadece oyuncu kimliginin icerigini temizle
		for (auto p = pText[playerid]->begin(); p != pText[playerid]->end(); p++)
		{
			// Extra id kaldir
			delete p->second->extra_id;

			// Array verilerini kaldir
			delete p->second->array_data;

			// Data daki verileri kaldir
			delete p->second;
		}

		// Pointeri kaldir
		delete pText[playerid];
		pText[playerid] = nullptr;

		// Slot manager da ki kimlikleri temizle
		slot_manager_player::reset_id(playerid);
	}
	else
	{
		// playerid degeri -1 ve alti olursa tum oyuncu havuzunu temizle
		for (auto it = pText.begin(); it != pText.end(); it++)
		{
			if (pText[it->first] == nullptr) {
				continue;
			}

			for (auto p = pText[it->first]->begin(); p != pText[it->first]->end(); p++)
			{
				// Extra id kaldir
				delete p->second->extra_id;

				// Array verilerini kaldir
				delete p->second->array_data;

				// Data daki verileri kaldir
				delete p->second;
			}

			// Pointeri kaldir
			delete pText[it->first];
			pText[playerid] = nullptr;

			// Slot manager da ki kimlikleri temizle
			slot_manager_player::reset_id(it->first);
		}

		// Tum pointer listesini temizle
		pText.clear();
	}
}

void PlayerText::Reload(int playerid, std::unordered_map<int, Text_Data*>::iterator it)
{
	if (it->second->real_id == INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		int text_id = CreatePlayerTextDraw(playerid, it->second->create_x, it->second->create_y, it->second->text.c_str());

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