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

#include "textdraw_data.hpp"
#include "natives.hpp"
#include "service.hpp"

bool Plugin_Settings::logMode = true;
std::string Plugin_Settings::file = "unknown";
int Plugin_Settings::line;

cell AMX_NATIVE_CALL Natives::TDLogger(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	Plugin_Settings::file = service::getString(amx, params[1]);
	Plugin_Settings::line = static_cast<int>(params[2]);
	return 1;
}

void Plugin_Settings::ILogger(LogType type, std::string funcs, int playerid, int textid)
{
	if (Plugin_Settings::logMode == true)
	{
		if (type == LogType::CREATE_PLAYER_TEXTDRAW)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First use the CreatePlayerTextDraw function. (playerid: %d, textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				playerid,
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == LogType::FIND_PLAYER_TEXT)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: No such id was found. (playerid: %d, textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				playerid,
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == LogType::SHOW_LIMIT_PLAYER)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: A maximum of %d textdraws can be displayed on a player. (playerid: %d, textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				MAX_PLAYER_TEXT_DRAWS,
				playerid,
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == LogType::FIND_GLOBAL_TEXT)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: No such id was found. (textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == LogType::INVALID_TYPE)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid. (%s:%d)"
			,
				funcs.c_str(),
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
	}
}