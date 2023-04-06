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

#include "sampgdk.h"

#define CHECK_PARAMS(n) \
	if (params[0] != (n * 4)) \
	{ \
		sampgdk::logprintf("%s: Expecting %d parameter(s), but found %d.", __func__, n, params[0] / sizeof(cell)); \
		return 0; \
	}

namespace Natives
{
	// Player Textdraw
	cell AMX_NATIVE_CALL CreatePTextDraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL DestroyPTextdraw(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextLetterSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextSize(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextAlignment(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextColor(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextUseBox(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextBoxColor(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextShadow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextOutline(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextBGColor(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextFont(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextProportional(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextSelectable(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextShow(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextHide(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextSetString(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextPreviewModel(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextPreviewRot(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PTextPreviewVehCol(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsValidPlayerTextDraw__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL IsPlayerTextDrawVisible__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetString__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawSetPos__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetLetterSize__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetTextSize__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetPos__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetColor__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetBoxColor__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetBGColor__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetShadow__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetOutline__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetFont__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawIsBox__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawIsProportional__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawIsSelectable__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetAlignment__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetPreviewModel__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetPreviewRot__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetPreviewVehCo__(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawSetExtraID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetExtraID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawResetExtraID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawSetArrayData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetArrayData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawRemoveArrayData(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawGetRealID(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL PlayerTextDrawSize(AMX* amx, cell* params);
	
};