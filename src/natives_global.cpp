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
	CHECK_MIN_PARAMS(3);

	const int textid = slot_manager_global::get_id();

	Text_Data& data = GlobalText::gText[textid];
	data = Text_Data();
	data.create_x = amx_ctof(params[1]);
	data.create_y = amx_ctof(params[2]);
	data.text = service::formattedString(amx, params, 3, 4);

	return static_cast<cell>(textid);
}

//
// native DestroyDynamicTextDraw(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DestroyDynamicTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	GlobalText::DestroyReal(*data);

	slot_manager_global::remove_id(textid);

	// Erase the outer entry too: clearing only the inner set left one empty set
	// behind per textdraw ever created.
	GlobalText::gTextVisible.erase(textid);
	GlobalText::gText.erase(textid);

	return 1;
}

//
// native DynamicTextDrawLetterSize(Text:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawLetterSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->lettersize_x = amx_ctof(params[2]);
	data->lettersize_y = amx_ctof(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawLetterSize(data->real_id, data->lettersize_x, data->lettersize_y);
	}

	return 1;
}

//
// native DynamicTextDrawTextSize(Text:textid, Float:width, Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->textsize_x = amx_ctof(params[2]);
	data->textsize_y = amx_ctof(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawTextSize(data->real_id, data->textsize_x, data->textsize_y);
	}

	return 1;
}

//
// native DynamicTextDrawAlignment(Text:textid, alignment, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->alignment = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawAlignment(data->real_id, data->alignment);
	}

	return 1;
}

//
// native DynamicTextDrawColour(Text:textid, textColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->color = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawColor(data->real_id, data->color);
	}

	return 1;
}

//
// native DynamicTextDrawUseBox(Text:textid, enableBox, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawUseBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->usebox = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawUseBox(data->real_id, data->usebox);
	}

	return 1;
}

//
// native DynamicTextDrawBoxColour(Text:textid, boxColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->boxcolor = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawBoxColor(data->real_id, data->boxcolor);
	}

	return 1;
}

//
// native DynamicTextDrawSetShadow(Text:textid, shadowSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->shadow = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetShadow(data->real_id, data->shadow);
	}

	return 1;
}

//
// native DynamicTextDrawSetOutline(Text:textid, outlineSize, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->outline = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetOutline(data->real_id, data->outline);
	}

	return 1;
}

//
// native DynamicTextDrawBackgroundColour(Text:textid, backgroundColour, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->backgroundcolor = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawBackgroundColor(data->real_id, data->backgroundcolor);
	}

	return 1;
}

//
// native DynamicTextDrawFont(Text:textid, font, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->font = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawFont(data->real_id, data->font);
	}

	return 1;
}

//
// native DynamicTextDrawSetProportional(Text:textid, proportional, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->proportional = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetProportional(data->real_id, data->proportional);
	}

	return 1;
}

//
// native DynamicTextDrawSetSelectable(Text:textid, selectable, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->selectable = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetSelectable(data->real_id, data->selectable);
	}

	return 1;
}

//
// native DynamicTextDrawShowForPlayer(playerid, Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawShowForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	// Reload is a no-op when the textdraw is already allocated server-side.
	if (!GlobalText::Reload(textid, *data))
	{
		Plugin_Settings::ILogger(LogType::SHOW_LIMIT_GLOBAL, __func__, playerid, textid);
		return 0;
	}

	GlobalText::gTextVisible[textid].insert(playerid);
	data->visible = true;

	TextDrawShowForPlayer(playerid, data->real_id);
	return 1;
}

//
// native DynamicTextDrawHideForPlayer(playerid, Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawHideForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	std::unordered_set<int>& viewers = GlobalText::gTextVisible[textid];
	viewers.erase(playerid);

	if (!viewers.empty())
	{
		if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
			TextDrawHideForPlayer(playerid, data->real_id);
		}
	}
	else
	{
		// Nobody is looking at it any more, so give the slot back to the server.
		// DestroyReal is a no-op when no server-side textdraw exists, which the
		// unguarded TextDrawDestroy here previously was not.
		GlobalText::DestroyReal(*data);
		data->visible = false;
	}

	return 1;
}

//
// native DynamicTextDrawShowForAll(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawShowForAll(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[2], params[3]);

	if (GlobalText::PlayerList.empty()) {
		return 0;
	}

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	if (!GlobalText::Reload(textid, *data))
	{
		Plugin_Settings::ILogger(LogType::SHOW_LIMIT_GLOBAL, __func__, INVALID_PLAYER_ID, textid);
		return 0;
	}

	std::unordered_set<int>& viewers = GlobalText::gTextVisible[textid];
	viewers.insert(GlobalText::PlayerList.begin(), GlobalText::PlayerList.end());
	data->visible = true;

	TextDrawShowForAll(data->real_id);
	return 1;
}

//
// native DynamicTextDrawHideForAll(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawHideForAll(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	GlobalText::gTextVisible[textid].clear();
	GlobalText::DestroyReal(*data);
	data->visible = false;

	return 1;
}

//
// native DynamicTextDrawSetString(Text:textid, const format[], {Float, _}:...);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetString(AMX* amx, cell* params)
{
	CHECK_MIN_PARAMS(2);

	const int textid = static_cast<int>(params[1]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->text = service::formattedString(amx, params, 2, 3);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetString(data->real_id, data->text.c_str());
	}

	return 1;
}

//
// native DynamicTextDrawSetPreviewModel(Text:textid, model, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->modelindex = static_cast<int>(params[2]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetPreviewModel(data->real_id, data->modelindex);
	}

	return 1;
}

//
// native DynamicTextDrawSetPreviewRot(Text:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(7);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[6], params[7]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->fRotX = amx_ctof(params[2]);
	data->fRotY = amx_ctof(params[3]);
	data->fRotZ = amx_ctof(params[4]);
	data->fZoom = amx_ctof(params[5]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetPreviewRot(data->real_id, data->fRotX, data->fRotY, data->fRotZ, data->fZoom);
	}

	return 1;
}

//
// native DynamicTextDrawSetPreviewVehCol(Text:textid, colour1, colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->veh_col1 = static_cast<int>(params[2]);
	data->veh_col2 = static_cast<int>(params[3]);

	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW) {
		TextDrawSetPreviewVehCol(data->real_id, data->veh_col1, data->veh_col2);
	}

	return 1;
}

//
// native IsValidDynamicTextDraw(Text:textid);
//
cell AMX_NATIVE_CALL Natives::IsValidDynamicTextDraw(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	return GlobalText::gText.find(static_cast<int>(params[1])) != GlobalText::gText.end();
}

//
// native IsDynTextDrawVisibleForPlayer(playerid, Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::IsDynamicTextDrawVisibleForPlayer(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	const int playerid = static_cast<int>(params[1]);
	const int textid = static_cast<int>(params[2]);
	Plugin_Settings::SetContext(amx, params[3], params[4]);

	if (GlobalText::Find(textid, __func__) == nullptr) {
		return 0;
	}

	auto viewers = GlobalText::gTextVisible.find(textid);
	if (viewers == GlobalText::gTextVisible.end()) {
		return 0;
	}

	return viewers->second.find(playerid) != viewers->second.end();
}

//
// native DynamicTextDrawGetString(Text:textid, string[], stringSize = sizeof(string));
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetString(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	return service::setString(amx, params[2], params[3], data->text);
}

//
// native DynamicTextDrawSetPos(Text:textid, Float:x, Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawSetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	const int textid = static_cast<int>(params[1]);
	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(textid, __func__);
	if (data == nullptr) {
		return 0;
	}

	data->create_x = amx_ctof(params[2]);
	data->create_y = amx_ctof(params[3]);

	// Position is fixed at creation time, so an existing textdraw has to be
	// rebuilt for the move to take effect.
	if (data->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
	{
		const bool wasVisible = data->visible;

		GlobalText::DestroyReal(*data);

		if (!GlobalText::Reload(textid, *data))
		{
			Plugin_Settings::ILogger(LogType::SHOW_LIMIT_GLOBAL, __func__, INVALID_PLAYER_ID, textid);
			return 0;
		}

		// Re-show only to the players who could already see it. Showing it to
		// everyone in PlayerList, as this used to, made a move reveal a textdraw
		// to players it was never shown to.
		if (wasVisible)
		{
			auto viewers = GlobalText::gTextVisible.find(textid);
			if (viewers != GlobalText::gTextVisible.end())
			{
				for (int viewer : viewers->second) {
					TextDrawShowForPlayer(viewer, data->real_id);
				}
			}
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

	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[2], data->lettersize_x);
	service::setFloat(amx, params[3], data->lettersize_y);

	return 1;
}

//
// native DynamicTextDrawGetTextSize(Text:textid, &Float:width, &Float:height, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetTextSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[2], data->textsize_x);
	service::setFloat(amx, params[3], data->textsize_y);

	return 1;
}

//
// native DynamicTextDrawGetPos(Text:textid, &Float:x, &Float:y, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPos(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[2], data->create_x);
	service::setFloat(amx, params[3], data->create_y);

	return 1;
}

//
// native DynamicTextDrawGetColour(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->color);
}

//
// native DynamicTextDrawGetBoxColour(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetBoxColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->boxcolor);
}

//
// native DynamicTextDrawGetBackgroundCo(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetBackgroundColour(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->backgroundcolor);
}

//
// native DynamicTextDrawGetShadow(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetShadow(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->shadow);
}

//
// native DynamicTextDrawGetOutline(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetOutline(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->outline);
}

//
// native DynamicTextDrawGetFont(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetFont(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->font);
}

//
// native DynamicTextDrawIsBox(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsBox(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->usebox);
}

//
// native DynamicTextDrawIsProportional(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsProportional(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->proportional);
}

//
// native DynamicTextDrawIsSelectable(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawIsSelectable(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->selectable);
}

//
// native DynamicTextDrawGetAlignment(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetAlignment(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->alignment);
}

//
// native DynamicTextDrawGetPreviewModel(Text:textid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	Plugin_Settings::SetContext(amx, params[2], params[3]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	return (data == nullptr) ? 0 : static_cast<cell>(data->modelindex);
}

//
// native DynamicTextDrawGetPreviewRot(Text:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewRot(AMX* amx, cell* params)
{
	CHECK_PARAMS(7);

	Plugin_Settings::SetContext(amx, params[6], params[7]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setFloat(amx, params[2], data->fRotX);
	service::setFloat(amx, params[3], data->fRotY);
	service::setFloat(amx, params[4], data->fRotZ);
	service::setFloat(amx, params[5], data->fZoom);

	return 1;
}

//
// native DynamicTextDrawGetPreviewVehCo(Text:textid, &colour1, &colour2, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetPreviewVehicleColours(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);

	Plugin_Settings::SetContext(amx, params[4], params[5]);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setInt(amx, params[2], data->veh_col1);
	service::setInt(amx, params[3], data->veh_col2);

	return 1;
}

//
// native DynamicTextDrawGetRealID(Text:textid, &Text:realid, const file[], line);
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetRealID(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);

	Plugin_Settings::SetContext(amx, params[3], params[4]);

	service::setInt(amx, params[2], INVALID_DYNAMIC_PLAYER_TEXTDRAW);

	Text_Data* data = GlobalText::Find(static_cast<int>(params[1]), __func__);
	if (data == nullptr) {
		return 0;
	}

	service::setInt(amx, params[2], data->real_id);

	return 1;
}

//
// native DynamicTextDrawGetSize();
//
cell AMX_NATIVE_CALL Natives::DynamicTextDrawGetSize(AMX* amx, cell* params)
{
	CHECK_PARAMS(0);
	return static_cast<cell>(GlobalText::gText.size());
}
