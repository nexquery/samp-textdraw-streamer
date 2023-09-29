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

#pragma once

#include "sampgdk.hpp"

#define CHECK_PARAMS(n) \
	if (params[0] != (n * 4)) \
	{ \
		sampgdk::logprintf("%s: Expecting %d parameter(s), but found %d.", __func__, n, params[0] / sizeof(cell)); \
		return 0; \
	}

namespace Natives
{
	// Global TextDraw
	cell AMX_NATIVE_CALL CreateDynamicTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DestroyDynamicTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawLetterSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawTextSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawAlignment(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawUseBox(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawBoxColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetShadow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetOutline(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawBackgroundColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawFont(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetProportional(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetSelectable(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawShowForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawHideForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawShowForAll(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawHideForAll(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetString(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetPreviewModel(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetPreviewRot(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetPreviewVehicleColours(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsValidDynamicTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsDynamicTextDrawVisibleForPlayer(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetString(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawSetPos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetLetterSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetTextSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetPos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetBoxColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetBackgroundColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetShadow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetOutline(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetFont(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawIsBox(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawIsProportional(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawIsSelectable(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetAlignment(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetPreviewModel(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetPreviewRot(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetPreviewVehicleColours(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetRealID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDrawGetSize(AMX* amx, cell* params);

	// Player TextDraw
	cell AMX_NATIVE_CALL CreateDynamicPlayerTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DestroyDynamicPlayerTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawLetterSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawTextSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawAlignment(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawUseBox(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawBoxColor(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetShadow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetOutline(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawBackgroundColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawFont(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetProportional(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetSelectable(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawShow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawHide(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetString(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetPreviewModel(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetPreviewRot(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetPreviewVehicleColours(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsValidDynamicPlayerTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsDynamicPlayerTextDrawVisible(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetString(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawSetPos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetLetterSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetTextSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetPos(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetBoxColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetBackgroundColour(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetShadow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetOutline(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetFont(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawIsBox(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawIsProportional(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawIsSelectable(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetAlignment(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetPreviewModel(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetPreviewRot(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicPlayerTextDrawGetPreviewVehicleColours(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetRealID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetSize(AMX* amx, cell* params);

	// Data (Int)
	cell AMX_NATIVE_CALL DynamicTextDraw_SetIntData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDraw_GetIntData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDraw_ClearIntData(AMX* amx, cell* params);

	// Data (Float)
	cell AMX_NATIVE_CALL DynamicTextDraw_SetFloatData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDraw_GetFloatData(AMX* amx, cell* params);

	// Data (Array)
	cell AMX_NATIVE_CALL DynamicTextDraw_SetArrayData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDraw_GetArrayData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DynamicTextDraw_ClearArrayData(AMX* amx, cell* params);

	// Logger
	cell AMX_NATIVE_CALL TDLogger(AMX* amx, cell* params);
};