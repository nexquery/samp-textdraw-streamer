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
	Text_Data* data			= new Text_Data();
	data->real_id			= -1;
	data->create_x			= amx_ctof(params[2]);
	data->create_y			= amx_ctof(params[3]);
	data->text				= service::formattedString(amx, params, 4, 5);
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

	// Veriyi pointera aktar
	PlayerText::pText[playerid]->emplace(auto_increment, data);
	return static_cast<int>(auto_increment);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(2);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Silmek istedigi veri var mi ?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		// Textdraw varsa kaldir
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawDestroy(playerid, it->second->real_id);
			it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
		}

		// Bu kimligi slot_manager icerisine aktar ve daha sonradan tekrar kullanilabilir hale getir
		slot_manager_player::remove_id(playerid, static_cast<int>(params[2]));

		// Extra id kaldir
		delete it->second->extra_id;

		// Array verilerini kaldir
		delete it->second->array_data;

		// Data daki verileri kaldir
		delete it->second;

		// Textdrawi listeden kaldir
		PlayerText::pText[playerid]->erase(it);

		// Silme islemi basarili
		return 1;
	}
	else
	{
		// Silme islemi basarisiz
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawLetterSize(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(4);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->lettersize_x = amx_ctof(params[3]);
		it->second->lettersize_y = amx_ctof(params[4]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawLetterSize(playerid, it->second->real_id, it->second->lettersize_x, it->second->lettersize_y);
		}

		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawTextSize(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(4);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->textsize_x = amx_ctof(params[3]);
		it->second->textsize_y = amx_ctof(params[4]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawTextSize(playerid, it->second->real_id, it->second->textsize_x, it->second->textsize_y);
		}

		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawAlignment(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->alignment = static_cast<int>(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawAlignment(playerid, it->second->real_id, it->second->alignment);
		}

		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawColour(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->color = static_cast<int>(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawColor(playerid, it->second->real_id, it->second->color);
		}

		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawUseBox(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->usebox = static_cast<int>(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawUseBox(playerid, it->second->real_id, it->second->usebox);
		}

		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawBoxColor(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->boxcolor = static_cast<int>(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawBoxColor(playerid, it->second->real_id, it->second->boxcolor);
		}

		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetShadow(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->shadow = static_cast<int>(params[3]);
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetShadow(playerid, it->second->real_id, it->second->shadow);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetOutline(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->outline = static_cast<int>(params[3]);
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetOutline(playerid, it->second->real_id, it->second->outline);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawBackgroundColour(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->backgroundcolor = static_cast<int>(params[3]);
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawBackgroundColor(playerid, it->second->real_id, it->second->backgroundcolor);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawFont(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->font = static_cast<int>(params[3]);
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawFont(playerid, it->second->real_id, it->second->font);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetProportional(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->proportional = static_cast<int>(params[3]);
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetProportional(playerid, it->second->real_id, it->second->proportional);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetSelectable(AMX* amx, cell* params)
{
	// Parametleri kontrol et
	CHECK_PARAMS(3);

	// Oyuncu kimligini al
	int playerid = static_cast<int>(params[1]);

	// Pointer var mi ?
	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	// Guncellenmek istenen veri var mi?
	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->selectable = static_cast<int>(params[3]);
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetSelectable(playerid, it->second->real_id, it->second->selectable);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawShow(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		if (it->second->real_id == INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			int text_id = CreatePlayerTextDraw(playerid, it->second->create_x, it->second->create_y, it->second->text.c_str());
			if (text_id == INVALID_TEXT_DRAW)
			{
				if (Plugin_Settings::logMode)
				{
					sampgdk::logprintf("[textdraw.streamer] %s: A maximum of %d textdraws can be displayed on a player.", __func__, MAX_PLAYER_TEXT_DRAWS);
				}
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
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawHide(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawDestroy(playerid, it->second->real_id);
			it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));

	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->text = service::formattedString(amx, params, 3, 4);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetString(playerid, it->second->real_id, it->second->text.c_str());
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));

	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->modelindex = static_cast<int>(params[3]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetPreviewModel(playerid, it->second->real_id, it->second->modelindex);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));

	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->fRotX = amx_ctof(params[3]);
		it->second->fRotY = amx_ctof(params[4]);
		it->second->fRotZ = amx_ctof(params[5]);
		it->second->fZoom = amx_ctof(params[6]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetPreviewRot(playerid, it->second->real_id, it->second->fRotX, it->second->fRotY, it->second->fRotZ, it->second->fZoom);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));

	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->veh_col1 = static_cast<int>(params[3]);
		it->second->veh_col2 = static_cast<int>(params[4]);

		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawSetPreviewVehCol(playerid, it->second->real_id, it->second->veh_col1, it->second->veh_col2);
		}
		return 1;
	}
	else
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: An item with this ID (%d) could not be found.", __func__, static_cast<int>(params[2]));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicPlayerTextDrawVisible(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setString(amx, params[3], params[4], it->second->text.c_str());
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		it->second->create_x = amx_ctof(params[3]);
		it->second->create_y = amx_ctof(params[4]);
	
		if (it->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
		{
			PlayerTextDrawDestroy(playerid, it->second->real_id);
			it->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
		}

		PlayerText::Reload(playerid, it);

		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setFloat(amx, params[3], it->second->lettersize_x);
		service::setFloat(amx, params[4], it->second->lettersize_y);
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setFloat(amx, params[3], it->second->textsize_x);
		service::setFloat(amx, params[4], it->second->textsize_y);
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setFloat(amx, params[3], it->second->create_x);
		service::setFloat(amx, params[4], it->second->create_y);
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->color);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->boxcolor);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->backgroundcolor);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->shadow);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->outline);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->font);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->usebox);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->proportional);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->selectable);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->alignment);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		return static_cast<int>(it->second->modelindex);
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setFloat(amx, params[3], it->second->fRotX);
		service::setFloat(amx, params[4], it->second->fRotY);
		service::setFloat(amx, params[5], it->second->fRotZ);
		service::setFloat(amx, params[6], it->second->fZoom);
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setInt(amx, params[3], it->second->veh_col1);
		service::setInt(amx, params[4], it->second->veh_col2);
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Natives::PlayerTextDrawGetRealID(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		if (Plugin_Settings::logMode)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		}
		service::setInt(amx, params[3], INVALID_DYNAMIC_PLAYER_TEXTDRAW);
		return 0;
	}

	auto it = PlayerText::pText[playerid]->find(static_cast<int>(params[2]));
	if (it != PlayerText::pText[playerid]->end())
	{
		service::setInt(amx, params[3], it->second->real_id);
	}
	return 1;
}

cell AMX_NATIVE_CALL Natives::PlayerTextDrawGetSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);

	int playerid = static_cast<int>(params[1]);

	if (PlayerText::pText[playerid] == nullptr)
	{
		sampgdk::logprintf("[textdraw.streamer] %s: First create the player textdraw.", __func__);
		return 0;
	}

	return (PlayerText::pText[playerid]->empty()) ? (0) : (PlayerText::pText[playerid]->size());
}