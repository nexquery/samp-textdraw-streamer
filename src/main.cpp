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

#include <set>
#include "sampgdk.h"
#include "compilation_date.hpp"
#include "plugin_version.hpp"
#include "slot_manager.hpp"
#include "natives.hpp"
#include "player_textdraw.hpp"

bool load = false;
extern void *pAMXFunctions;
std::set<AMX*> gAmx;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return sampgdk::Supports() | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	load = sampgdk::Load(ppData);
	if (load)
	{
		sampgdk::logprintf("");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |    textdraw-streamer v%d.%d.%d   |", MINOR, MAJOR, PATCH);
		sampgdk::logprintf(" |            Loaded             |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Coding:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Burak (Nexor)                |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Compiled:                    |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  %02d.%02d.%04d, %02d:%02d:%02d         |", BUILD_DAY, BUILD_MONTH, BUILD_YEAR, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Github:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  github.com/nexquery          |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Discord:                     |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Nexor#4730                   |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf("");
	}
	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	if (load)
	{
		PlayerText::Destroy_PlayerText(-1);

		sampgdk::logprintf("");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |    textdraw-streamer v%d.%d.%d   |", MINOR, MAJOR, PATCH);
		sampgdk::logprintf(" |           Unloaded            |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Coding:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Burak (Nexor)                |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Compiled:                    |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  %02d.%02d.%04d, %02d:%02d:%02d         |", BUILD_DAY, BUILD_MONTH, BUILD_YEAR, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Github:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  github.com/nexquery          |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Discord:                     |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Nexor#4730                   |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf("");
	}
}

extern "C" const AMX_NATIVE_INFO NativeList[] =
{
	// Player Textdraw
	{"CreatePTextDraw", Natives::CreatePTextDraw},
	{"DestroyPTextdraw", Natives::DestroyPTextdraw},
	{"PTextLetterSize", Natives::PTextLetterSize},
	{"PTextSize", Natives::PTextSize},
	{"PTextAlignment", Natives::PTextAlignment},
	{"PTextColor", Natives::PTextColor},
	{"PTextUseBox", Natives::PTextUseBox},
	{"PTextBoxColor", Natives::PTextBoxColor},
	{"PTextShadow", Natives::PTextShadow},
	{"PTextOutline", Natives::PTextOutline},
	{"PTextBGColor", Natives::PTextBGColor},
	{"PTextFont", Natives::PTextFont},
	{"PTextProportional", Natives::PTextProportional},
	{"PTextSelectable", Natives::PTextSelectable},
	{"PTextShow", Natives::PTextShow},
	{"PTextHide", Natives::PTextHide},
	{"PTextSetString", Natives::PTextSetString},
	{"PTextPreviewModel", Natives::PTextPreviewModel},
	{"PTextPreviewRot", Natives::PTextPreviewRot},
	{"PTextPreviewVehCol", Natives::PTextPreviewVehCol},
	{"IsValidPlayerTextDraw__", Natives::IsValidPlayerTextDraw__},
	{"IsPlayerTextDrawVisible__", Natives::IsPlayerTextDrawVisible__},
	{"PlayerTextDrawGetString__", Natives::PlayerTextDrawGetString__},
	{"PlayerTextDrawSetPos__", Natives::PlayerTextDrawSetPos__},
	{"PlayerTextDrawGetLetterSize__", Natives::PlayerTextDrawGetLetterSize__},
	{"PlayerTextDrawGetTextSize__", Natives::PlayerTextDrawGetTextSize__},
	{"PlayerTextDrawGetPos__", Natives::PlayerTextDrawGetPos__},
	{"PlayerTextDrawGetColor__", Natives::PlayerTextDrawGetColor__},
	{"PlayerTextDrawGetBoxColor__", Natives::PlayerTextDrawGetBoxColor__},
	{"PlayerTextDrawGetBGColor__", Natives::PlayerTextDrawGetBGColor__},
	{"PlayerTextDrawGetShadow__", Natives::PlayerTextDrawGetShadow__},
	{"PlayerTextDrawGetOutline__", Natives::PlayerTextDrawGetOutline__},
	{"PlayerTextDrawGetFont__", Natives::PlayerTextDrawGetFont__},
	{"PlayerTextDrawIsBox__", Natives::PlayerTextDrawIsBox__},
	{"PlayerTextDrawIsProportional__", Natives::PlayerTextDrawIsProportional__},
	{"PlayerTextDrawIsSelectable__", Natives::PlayerTextDrawIsSelectable__},
	{"PlayerTextDrawGetAlignment__", Natives::PlayerTextDrawGetAlignment__},
	{"PlayerTextDrawGetPreviewModel__", Natives::PlayerTextDrawGetPreviewModel__},
	{"PlayerTextDrawGetPreviewRot__", Natives::PlayerTextDrawGetPreviewRot__},
	{"PlayerTextDrawGetPreviewVehCo__", Natives::PlayerTextDrawGetPreviewVehCo__},
	{"PlayerTextDrawSetExtraID", Natives::PlayerTextDrawSetExtraID},
	{"PlayerTextDrawGetExtraID", Natives::PlayerTextDrawGetExtraID},
	{"PlayerTextDrawResetExtraID", Natives::PlayerTextDrawResetExtraID},
	{"PlayerTextDrawSetArrayData", Natives::PlayerTextDrawSetArrayData},
	{"PlayerTextDrawGetArrayData", Natives::PlayerTextDrawGetArrayData},
	{"PlayerTextDrawRemoveArrayData", Natives::PlayerTextDrawRemoveArrayData},
	{"PlayerTextDrawGetRealID", Natives::PlayerTextDrawGetRealID},
	{"PlayerTextDrawSize", Natives::PlayerTextDrawSize},

	// NULL
	{NULL, NULL}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	gAmx.insert(amx);
	return amx_Register(amx, NativeList, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	gAmx.erase(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	// PlayerTextdraw havuzunu ve slot manageri temizle
	PlayerText::Destroy_PlayerText(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid)
{
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	return false;
}