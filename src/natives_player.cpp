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
// native PlayerText:CreateDynamicPlayerTextDraw(playerid, Float:x, Float:y, const format[], {Float, _}:...);
//
cell AMX_NATIVE_CALL Natives::CreateDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	CHECK_MIN_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);

	TextMap* pool = PlayerText::Ensure(playerid);
	if (pool == nullptr) {
		return INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	}

	const int textid = slot_manager_player::get_id(playerid);

	Text_Data& data = (*pool)[textid];
	data = Text_Data();
	data.create_x = amx_ctof(params[2]);
	data.create_y = amx_ctof(params[3]);
	data.text = service::formattedString(amx, params, 4, 5);

	return static_cast<cell>(textid);
}

//
// native DestroyDynamicPlayerTextDraw(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DestroyDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	PlayerText::DestroyReal(playerid, *data);

	slot_manager_player::remove_id(playerid, textid);
	PlayerText::Pool(playerid)->erase(textid);

	return 1;
}

//
// native DynamicPlayerTextDrawLetterSize(playerid, PlayerText:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->lettersize_x = amx_ctof(params[3]);
	data->lettersize_y = amx_ctof(params[4]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawLetterSize(playerid, data->real_id, data->lettersize_x, data->lettersize_y);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawTextSize(playerid, PlayerText:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->textsize_x = amx_ctof(params[3]);
	data->textsize_y = amx_ctof(params[4]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawTextSize(playerid, data->real_id, data->textsize_x, data->textsize_y);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawAlignment(playerid, PlayerText:textid, alignment, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->alignment = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawAlignment(playerid, data->real_id, data->alignment);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawColour(playerid, PlayerText:textid, textColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->color = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawColor(playerid, data->real_id, data->color);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawUseBox(playerid, PlayerText:textid, enableBox, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawUseBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->usebox = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawUseBox(playerid, data->real_id, data->usebox);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawBoxColor(playerid, PlayerText:textid, boxColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawBoxColor(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->boxcolor = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawBoxColor(playerid, data->real_id, data->boxcolor);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetShadow(playerid, PlayerText:textid, shadowSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->shadow = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetShadow(playerid, data->real_id, data->shadow);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetOutline(playerid, PlayerText:textid, outlineSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->outline = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetOutline(playerid, data->real_id, data->outline);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawBGColour(playerid, PlayerText:textid, backgroundColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->backgroundcolor = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawBackgroundColor(playerid, data->real_id, data->backgroundcolor);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawFont(playerid, PlayerText:textid, font, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->font = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawFont(playerid, data->real_id, data->font);
	}

	return 1;
}

//
// native DynPlayerTextSetProportional(playerid, PlayerText:textid, proportional, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->proportional = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetProportional(playerid, data->real_id, data->proportional);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSelectable(playerid, PlayerText:textid, selectable, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->selectable = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetSelectable(playerid, data->real_id, data->selectable);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawShow(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawShow(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	// Reload creates and configures the textdraw, and is a no-op when one already
	// exists. This used to be ~70 lines duplicated from PlayerText::Reload.
	if (!PlayerText::Reload(playerid, *data))
	{
		Plugin_Settings::ILogger(LogType::SHOW_LIMIT_PLAYER, __func__, playerid, textid);
		return 0;
	}

	data->visible = true;
	PlayerTextDrawShow(playerid, data->real_id);

	return 1;
}

//
// native DynamicPlayerTextDrawHide(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawHide(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	// Destroying rather than hiding is what frees the player's slot, which is the
	// point of the streamer.
	PlayerText::DestroyReal(playerid, *data);
	data->visible = false;

	return 1;
}

//
// native DynamicPlayerTextDrawSetString(playerid, PlayerText:textid, const format[], {Float, _}:...);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetString(AMX* amx, cell* params)
{
	CHECK_MIN_PARAMS(3);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->text = service::formattedString(amx, params, 3, 4);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetString(playerid, data->real_id, data->text.c_str());
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetPrevMdl(playerid, PlayerText:textid, model, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->modelindex = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetPreviewModel(playerid, data->real_id, data->modelindex);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawSetPrevRot(playerid, PlayerText:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[7], params[8]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->fRotX = amx_ctof(params[3]);
	data->fRotY = amx_ctof(params[4]);
	data->fRotZ = amx_ctof(params[5]);
	data->fZoom = amx_ctof(params[6]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetPreviewRot(playerid, data->real_id, data->fRotX, data->fRotY, data->fRotZ, data->fZoom);
	}

	return 1;
}

//
// native DynamicPlayerTextDrawPrevVehCol(playerid, PlayerText:textid, colour1, colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->veh_col1 = static_cast<int>(params[3]);
	data->veh_col2 = static_cast<int>(params[4]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		PlayerTextDrawSetPreviewVehCol(playerid, data->real_id, data->veh_col1, data->veh_col2);
	}

	return 1;
}

//
// native IsValidDynamicPlayerTextDraw(playerid, PlayerText:textid);
//
cell AMX_NATIVE_CALL Natives::IsValidDynamicPlayerTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	TextMap* pool = PlayerText::Pool(playerid);
	if (pool == nullptr) {
		return 0;
	}

	return pool->find(textid) != pool->end();
}

//
// native IsDynamicPlayerTextDrawVisible(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::IsDynamicPlayerTextDrawVisible(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	return data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW;
}

//
// native DynamicPlayerTextDrawGetString(playerid, PlayerText:textid, string[], stringSize = sizeof(string));
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	return service::setString(amx, params[3], params[4], data->text);
}

//
// native DynamicPlayerTextDrawSetPos(playerid, PlayerText:textid, Float:x, Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawSetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->create_x = amx_ctof(params[3]);
	data->create_y = amx_ctof(params[4]);

	// Position is fixed at creation time, so an existing textdraw has to be
	// rebuilt for the move to take effect.
	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		const bool wasVisible = data->visible;

		PlayerText::DestroyReal(playerid, *data);

		if (!PlayerText::Reload(playerid, *data))
		{
			Plugin_Settings::ILogger(LogType::SHOW_LIMIT_PLAYER, __func__, playerid, textid);
			return 0;
		}

		// Only put it back on screen if it was on screen to begin with; this used
		// to show a hidden textdraw as a side effect of moving it.
		if (wasVisible) {
			PlayerTextDrawShow(playerid, data->real_id);
		}
	}

	return 1;
}

//
// native DynPlayerTextDrawGetLetterSize(playerid, PlayerText:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[3], data->lettersize_x);
	service::setFloat(amx, params[4], data->lettersize_y);

	return 1;
}

//
// native DynPlayerTextDrawGetTextSize(playerid, PlayerText:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[3], data->textsize_x);
	service::setFloat(amx, params[4], data->textsize_y);

	return 1;
}

//
// native DynamicPlayerTextDrawGetPos(playerid, PlayerText:textid, &Float:x, &Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[3], data->create_x);
	service::setFloat(amx, params[4], data->create_y);

	return 1;
}

//
// native DynamicPlayerTextDrawGetColour(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->color);
}

//
// native DynamicPlayerTextDrawGetBoxCol(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->boxcolor);
}

//
// native DynPlayerTextDrawGetBGColour(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->backgroundcolor);
}

//
// native DynamicPlayerTextDrawGetShadow(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->shadow);
}

//
// native DynamicPlayerTextDrawGetOutline(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->outline);
}

//
// native DynamicPlayerTextDrawGetFont(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->font);
}

//
// native DynamicPlayerTextDrawIsBox(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->usebox);
}

//
// native DynPlayerTextDrawIsProportional(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->proportional);
}

//
// native DynPlayerTextDrawIsSelectable(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawIsSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->selectable);
}

//
// native DynPlayerTextDrawGetAlignment(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->alignment);
}

//
// native DynPlayerTextDrawGetPreviewMdl(playerid, PlayerText:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = PlayerText::Find(static_cast<int>(params[1]), static_cast<int>(params[2]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->modelindex);
}

//
// native DynPlayerTextDrawGetPreviewRot(playerid, PlayerText:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[7], params[8]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[3], data->fRotX);
	service::setFloat(amx, params[4], data->fRotY);
	service::setFloat(amx, params[5], data->fRotZ);
	service::setFloat(amx, params[6], data->fZoom);

	return 1;
}

//
// native DynPlayerTextDrawGetPrevVehCol(playerid, PlayerText:textid, &colour1, &colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicPlayerTextDrawGetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(6);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[5], params[6]);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setInt(amx, params[3], data->veh_col1);
	service::setInt(amx, params[4], data->veh_col2);

	return 1;
}

//
// native PlayerTextDrawGetRealID(playerid, PlayerText:text, &PlayerText:realid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::PlayerTextDrawGetRealID(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	service::setInt(amx, params[3], INVALID_DYNAMIC_PLAYER_TEXTDRAW);

	Text_Data* data = PlayerText::Find(playerid, textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setInt(amx, params[3], data->real_id);

	return 1;
}

//
// native PlayerTextDrawGetSize(playerid);
//
cell AMX_NATIVE_CALL Natives::PlayerTextDrawGetSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);

	const int playerid = static_cast<int>(params[1]);

	if (GlobalText::PlayerList.find(playerid) == GlobalText::PlayerList.end()) {
		return 0;
	}

	TextMap* pool = PlayerText::Pool(playerid);
	if (pool == nullptr)
	{
		Plugin_Settings::ILogger(LogType::CREATE_PLAYER_TEXTDRAW, __func__, playerid, 0);
		return 0;
	}

	return static_cast<cell>(pool->size());
}
