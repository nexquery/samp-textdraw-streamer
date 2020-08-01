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
#include	"Servis.h"
#include	"Item.h"
#include	"Servis.h"

class Natives
{
public:

	// Player Textdraw Fonksiyonları
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
};