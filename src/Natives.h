/*
 * Copyright (C) 2020 Burak (NexoR)
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

#include	"Makro.h"
#include	"SlotManager.h"
#include	"Item.h"
#include	"Servis.h"

class Natives
{
public:

	// Player Textdraw Fonksiyonlarý
	static cell AMX_NATIVE_CALL CreatePTextdraw(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL DestroyPTextdraw(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextLetterSize(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextSize(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextAlignment(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextColor(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextUseBox(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextBoxColor(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextShadow(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextOutline(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextBGColor(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextFont(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextProportional(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextSelectable(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextShow(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextHide(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextSetString(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextPreviewModel(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextPreviewRot(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PTextPreviewVehCol(AMX* amx, cell* params);

	// Player Textdraw Verilerini Okuma
	static cell AMX_NATIVE_CALL IsValidPlayerTextDraw(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL IsPlayerTextDrawVisible(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetString(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawSetPos(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetLetterSize(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetTextSize(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetPos(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetColor(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetBoxColor(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetBackgroundCol(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetShadow(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetOutline(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetFont(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawIsBox(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawIsProportional(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawIsSelectable(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetAlignment(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetPreviewModel(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetPreviewRot(AMX* amx, cell* params);
	static cell AMX_NATIVE_CALL PlayerTextDrawGetPreviewVehCol(AMX* amx, cell* params);
};