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

#include "player_textdraw.hpp"
#include "slot_manager.hpp"
#include "sampgdk.h"

DefaultText PlayerText::Default;
std::unordered_map<int, std::unordered_map<int, PlayerData*>*> PlayerText::pText;

void PlayerText::Destroy_PlayerText(int playerid)
{
	if (playerid >= 0 && playerid <= 1000)
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
		slot_manager::reset_id(playerid);
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
			slot_manager::reset_id(it->first);
		}

		// Tum pointer listesini temizle
		pText.clear();
	}
}

void PlayerText::pText_Reload(int playerid, int textid)
{
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(textid));
	if (it != PlayerText::pText[playerid]->end())
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
}