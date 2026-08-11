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
#include "sampgdk.hpp"
#include "compilation_date.hpp"
#include "plugin_version.hpp"
#include "slot_manager.hpp"
#include "natives.hpp"
#include "textdraw_data.hpp"

bool load = false;
extern void *pAMXFunctions;
std::set<AMX*> gAmx;

static void PrintBanner(const char* state)
{
	sampgdk::logprintf("");
	sampgdk::logprintf(" =================================");
	sampgdk::logprintf(" |                               |");
	sampgdk::logprintf(" |    textdraw-streamer v%d.%d.%d   |", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
	sampgdk::logprintf(" |            %-19s|", state);
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
	sampgdk::logprintf(" |  benburakya - Nexor#4730      |");
	sampgdk::logprintf(" |                               |");
	sampgdk::logprintf(" =================================");
	sampgdk::logprintf("");
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	load = sampgdk::Load(ppData);

	if (load) {
		PrintBanner("Loaded");
	}

	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	if (load)
	{
		GlobalText::Destroy();
		PlayerText::DestroyAll();

		PrintBanner("Unloaded");
	}
}

extern "C" const AMX_NATIVE_INFO NativeList[] =
{
	// Global
	{"CreateDynamicTextDraw",							Natives::CreateDynamicTextDraw},
	{"DestroyDynamicTextDraw",							Natives::DestroyDynamicTextDraw},
	{"DynamicTextDrawLetterSize",						Natives::DynamicTextDrawLetterSize},
	{"DynamicTextDrawTextSize",							Natives::DynamicTextDrawTextSize},
	{"DynamicTextDrawAlignment",						Natives::DynamicTextDrawAlignment},
	{"DynamicTextDrawColour",							Natives::DynamicTextDrawColour},
	{"DynamicTextDrawUseBox",							Natives::DynamicTextDrawUseBox},
	{"DynamicTextDrawBoxColour",						Natives::DynamicTextDrawBoxColour},
	{"DynamicTextDrawSetShadow",						Natives::DynamicTextDrawSetShadow},
	{"DynamicTextDrawSetOutline",						Natives::DynamicTextDrawSetOutline},
	{"DynamicTextDrawBackgroundColour",					Natives::DynamicTextDrawBackgroundColour},
	{"DynamicTextDrawFont",								Natives::DynamicTextDrawFont},
	{"DynamicTextDrawSetProportional",					Natives::DynamicTextDrawSetProportional},
	{"DynamicTextDrawSetSelectable",					Natives::DynamicTextDrawSetSelectable},
	{"DynamicTextDrawShowForPlayer",					Natives::DynamicTextDrawShowForPlayer},
	{"DynamicTextDrawHideForPlayer",					Natives::DynamicTextDrawHideForPlayer},
	{"DynamicTextDrawShowForAll",						Natives::DynamicTextDrawShowForAll},
	{"DynamicTextDrawHideForAll",						Natives::DynamicTextDrawHideForAll},
	{"DynamicTextDrawSetString",						Natives::DynamicTextDrawSetString},
	{"DynamicTextDrawSetPreviewModel",					Natives::DynamicTextDrawSetPreviewModel},
	{"DynamicTextDrawSetPreviewRot",					Natives::DynamicTextDrawSetPreviewRot},
	{"DynamicTextDrawSetPreviewVehCol",					Natives::DynamicTextDrawSetPreviewVehicleColours},

	{"IsValidDynamicTextDraw",							Natives::IsValidDynamicTextDraw},
	{"IsDynTextDrawVisibleForPlayer",					Natives::IsDynamicTextDrawVisibleForPlayer},
	{"DynamicTextDrawGetString",						Natives::DynamicTextDrawGetString},
	{"DynamicTextDrawSetPos",							Natives::DynamicTextDrawSetPos},
	{"DynamicTextDrawGetLetterSize",					Natives::DynamicTextDrawGetLetterSize},
	{"DynamicTextDrawGetTextSize",						Natives::DynamicTextDrawGetTextSize},
	{"DynamicTextDrawGetPos",							Natives::DynamicTextDrawGetPos},
	{"DynamicTextDrawGetColour",						Natives::DynamicTextDrawGetColour},
	{"DynamicTextDrawGetBoxColour",						Natives::DynamicTextDrawGetBoxColour},
	{"DynamicTextDrawGetBackgroundCo",					Natives::DynamicTextDrawGetBackgroundColour},
	{"DynamicTextDrawGetShadow",						Natives::DynamicTextDrawGetShadow},
	{"DynamicTextDrawGetOutline",						Natives::DynamicTextDrawGetOutline},
	{"DynamicTextDrawGetFont",							Natives::DynamicTextDrawGetFont},
	{"DynamicTextDrawIsBox",							Natives::DynamicTextDrawIsBox},
	{"DynamicTextDrawIsProportional",					Natives::DynamicTextDrawIsProportional},
	{"DynamicTextDrawIsSelectable",						Natives::DynamicTextDrawIsSelectable},
	{"DynamicTextDrawGetAlignment",						Natives::DynamicTextDrawGetAlignment},
	{"DynamicTextDrawGetPreviewModel",					Natives::DynamicTextDrawGetPreviewModel},
	{"DynamicTextDrawGetPreviewRot",					Natives::DynamicTextDrawGetPreviewRot},
	{"DynamicTextDrawGetPreviewVehCo",					Natives::DynamicTextDrawGetPreviewVehicleColours},
	{"DynamicTextDrawGetRealID",						Natives::DynamicTextDrawGetRealID},
	{"DynamicTextDrawGetSize",							Natives::DynamicTextDrawGetSize},

	// Player
	{"CreateDynamicPlayerTextDraw",						Natives::CreateDynamicPlayerTextDraw},
	{"DestroyDynamicPlayerTextDraw",					Natives::DestroyDynamicPlayerTextDraw},
	{"DynamicPlayerTextDrawLetterSize",					Natives::DynamicPlayerTextDrawLetterSize},
	{"DynamicPlayerTextDrawTextSize",					Natives::DynamicPlayerTextDrawTextSize},
	{"DynamicPlayerTextDrawAlignment",					Natives::DynamicPlayerTextDrawAlignment},
	{"DynamicPlayerTextDrawColour",						Natives::DynamicPlayerTextDrawColour},
	{"DynamicPlayerTextDrawUseBox",						Natives::DynamicPlayerTextDrawUseBox},
	{"DynamicPlayerTextDrawBoxColor",					Natives::DynamicPlayerTextDrawBoxColor},
	{"DynamicPlayerTextDrawSetShadow",					Natives::DynamicPlayerTextDrawSetShadow},
	{"DynamicPlayerTextDrawSetOutline",					Natives::DynamicPlayerTextDrawSetOutline},
	{"DynamicPlayerTextDrawBGColour",					Natives::DynamicPlayerTextDrawBackgroundColour},
	{"DynamicPlayerTextDrawFont",						Natives::DynamicPlayerTextDrawFont},
	{"DynPlayerTextSetProportional",					Natives::DynamicPlayerTextDrawSetProportional},
	{"DynamicPlayerTextDrawSelectable",					Natives::DynamicPlayerTextDrawSetSelectable},
	{"DynamicPlayerTextDrawShow",						Natives::DynamicPlayerTextDrawShow},
	{"DynamicPlayerTextDrawHide",						Natives::DynamicPlayerTextDrawHide},
	{"DynamicPlayerTextDrawSetString",					Natives::DynamicPlayerTextDrawSetString},
	{"DynamicPlayerTextDrawSetPrevMdl",					Natives::DynamicPlayerTextDrawSetPreviewModel},
	{"DynamicPlayerTextDrawSetPrevRot",					Natives::DynamicPlayerTextDrawSetPreviewRot},
	{"DynamicPlayerTextDrawPrevVehCol",					Natives::DynamicPlayerTextDrawSetPreviewVehicleColours},

	{"IsValidDynamicPlayerTextDraw",					Natives::IsValidDynamicPlayerTextDraw},
	{"IsDynamicPlayerTextDrawVisible",					Natives::IsDynamicPlayerTextDrawVisible},
	{"DynamicPlayerTextDrawGetString",					Natives::DynamicPlayerTextDrawGetString},
	{"DynamicPlayerTextDrawSetPos",						Natives::DynamicPlayerTextDrawSetPos},
	{"DynPlayerTextDrawGetLetterSize",					Natives::DynamicPlayerTextDrawGetLetterSize},
	{"DynPlayerTextDrawGetTextSize",					Natives::DynamicPlayerTextDrawGetTextSize},
	{"DynamicPlayerTextDrawGetPos",						Natives::DynamicPlayerTextDrawGetPos},
	{"DynamicPlayerTextDrawGetColour",					Natives::DynamicPlayerTextDrawGetColour},
	{"DynamicPlayerTextDrawGetBoxCol",					Natives::DynamicPlayerTextDrawGetBoxColour},
	{"DynPlayerTextDrawGetBGColour",					Natives::DynamicPlayerTextDrawGetBackgroundColour},
	{"DynamicPlayerTextDrawGetShadow",					Natives::DynamicPlayerTextDrawGetShadow},
	{"DynamicPlayerTextDrawGetOutline",					Natives::DynamicPlayerTextDrawGetOutline},
	{"DynamicPlayerTextDrawGetFont",					Natives::DynamicPlayerTextDrawGetFont},
	{"DynamicPlayerTextDrawIsBox",						Natives::DynamicPlayerTextDrawIsBox},
	{"DynPlayerTextDrawIsProportional",					Natives::DynamicPlayerTextDrawIsProportional},
	{"DynPlayerTextDrawIsSelectable",					Natives::DynamicPlayerTextDrawIsSelectable},
	{"DynPlayerTextDrawGetAlignment",					Natives::DynamicPlayerTextDrawGetAlignment},
	{"DynPlayerTextDrawGetPreviewMdl",					Natives::DynamicPlayerTextDrawGetPreviewModel},
	{"DynPlayerTextDrawGetPreviewRot",					Natives::DynamicPlayerTextDrawGetPreviewRot},
	{"DynPlayerTextDrawGetPrevVehCol",					Natives::DynamicPlayerTextDrawGetPreviewVehicleColours},
	{"PlayerTextDrawGetRealID",							Natives::PlayerTextDrawGetRealID},
	{"PlayerTextDrawGetSize",							Natives::PlayerTextDrawGetSize},

	// Data (Int)
	{"DynamicTextDraw_SetIntData",						Natives::DynamicTextDraw_SetIntData},
	{"DynamicTextDraw_GetIntData",						Natives::DynamicTextDraw_GetIntData},
	{"DynamicTextDraw_ClearIntData",					Natives::DynamicTextDraw_ClearIntData},

	// Data (Float)
	{"DynamicTextDraw_SetFloatData",					Natives::DynamicTextDraw_SetFloatData},
	{"DynamicTextDraw_GetFloatData",					Natives::DynamicTextDraw_GetFloatData},

	// Data (Array)
	{ "DynamicTextDraw_SetArrayData",					Natives::DynamicTextDraw_SetArrayData},
	{ "DynamicTextDraw_GetArrayData",					Natives::DynamicTextDraw_GetArrayData},
	{ "DynamicTextDraw_ClearArrayData",					Natives::DynamicTextDraw_ClearArrayData},

	// Logger
	{ "TDLogger__",										Natives::TDLogger },

	// NULL
	{NULL, NULL}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	cell address = 0;
	if (!amx_FindPubVar(amx, "TDS_Enable_Log", &address))
	{
		cell* amxPhysAddr = NULL;
		if (!amx_GetAddr(amx, address, &amxPhysAddr))
		{
			Plugin_Settings::logMode = static_cast<bool>(*amxPhysAddr);
		}
	}
	gAmx.insert(amx);
	return amx_Register(amx, NativeList, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	// The logger holds this AMX to resolve __file lazily; drop it before the
	// script goes away so a later message cannot read freed memory.
	Plugin_Settings::ClearContext(amx);

	gAmx.erase(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS) {
		GlobalText::PlayerList.insert(playerid);
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	for (auto& entry : GlobalText::gTextVisible)
	{
		// erase returns 0 when this player was not a viewer, so the lookup and the
		// removal are one operation instead of find-then-erase per textdraw.
		if (entry.second.erase(playerid) == 0) {
			continue;
		}

		// That was the last viewer, so hand the global slot back to the server.
		if (entry.second.empty())
		{
			auto it = GlobalText::gText.find(entry.first);
			if (it != GlobalText::gText.end())
			{
				GlobalText::DestroyReal(it->second);
				it->second.visible = false;
			}
		}
	}

	GlobalText::PlayerList.erase(playerid);

	// Frees the player's textdraw pool and resets their slot manager.
	PlayerText::Destroy(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid)
{
	if (gAmx.empty()) {
		return false;
	}

	int idx = 0;

	// The escape key.
	if (clickedid == INVALID_TEXT_DRAW)
	{
		for (AMX* amx : gAmx)
		{
			if (!amx_FindPublic(amx, "OnCancelDynamicTextDraw", &idx))
			{
				amx_Push(amx, static_cast<cell>(playerid));
				amx_Exec(amx, NULL, idx);
			}

			if (!amx_FindPublic(amx, "OnClickDynamicTextDraw", &idx))
			{
				amx_Push(amx, static_cast<cell>(INVALID_TEXT_DRAW));
				amx_Push(amx, static_cast<cell>(playerid));
				amx_Exec(amx, NULL, idx);
			}
		}

		return false;
	}

	// Reverse index, rather than scanning every global textdraw for a real_id.
	auto mapped = GlobalText::realToText.find(clickedid);
	if (mapped == GlobalText::realToText.end()) {
		return false;
	}

	for (AMX* amx : gAmx)
	{
		if (!amx_FindPublic(amx, "OnClickDynamicTextDraw", &idx))
		{
			amx_Push(amx, static_cast<cell>(mapped->second));
			amx_Push(amx, static_cast<cell>(playerid));
			amx_Exec(amx, NULL, idx);
		}
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	if (gAmx.empty()) {
		return false;
	}

	// Pool() does not insert, unlike the operator[] this replaces.
	TextMap* pool = PlayerText::Pool(playerid);
	if (pool == nullptr) {
		return false;
	}

	for (const auto& entry : *pool)
	{
		if (entry.second.real_id != playertextid) {
			continue;
		}

		int idx = 0;
		for (AMX* amx : gAmx)
		{
			if (!amx_FindPublic(amx, "OnClickDynamicPlayerTextDraw", &idx))
			{
				//	playerid, textid
				//
				//		|		|
				//
				//		0		1
				//
				amx_Push(amx, static_cast<cell>(entry.first));	//	1
				amx_Push(amx, static_cast<cell>(playerid));		//	0
				amx_Exec(amx, NULL, idx);
			}
		}

		break;
	}

	return false;
}
