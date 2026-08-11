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
AMX* Plugin_Settings::amx = nullptr;
cell Plugin_Settings::fileParam = 0;
int Plugin_Settings::line = 0;

cell AMX_NATIVE_CALL Natives::TDLogger(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	Plugin_Settings::SetContext(amx, params[1], params[2]);
	return 1;
}

namespace
{
	// Resolved only when a message is actually emitted, so the common path costs
	// three stores instead of an AMX string read and a heap allocation.
	std::string currentFile()
	{
		if (Plugin_Settings::amx == nullptr) {
			return std::string("unknown");
		}

		std::string file = service::getString(Plugin_Settings::amx, Plugin_Settings::fileParam);
		return file.empty() ? std::string("unknown") : file;
	}
}

void Plugin_Settings::ILogger(LogType type, const char* funcs, int playerid, int textid)
{
	if (!Plugin_Settings::logMode) {
		return;
	}

	const std::string file = currentFile();

	switch (type)
	{
		case LogType::CREATE_PLAYER_TEXTDRAW:
			sampgdk::logprintf("[textdraw.streamer] %s: First use the CreatePlayerTextDraw function. (playerid: %d, textId: %d) (%s:%d)",
				funcs, playerid, textid, file.c_str(), Plugin_Settings::line);
			break;

		case LogType::FIND_PLAYER_TEXT:
			sampgdk::logprintf("[textdraw.streamer] %s: No such id was found. (playerid: %d, textId: %d) (%s:%d)",
				funcs, playerid, textid, file.c_str(), Plugin_Settings::line);
			break;

		case LogType::SHOW_LIMIT_PLAYER:
			sampgdk::logprintf("[textdraw.streamer] %s: A maximum of %d textdraws can be displayed on a player. (playerid: %d, textId: %d) (%s:%d)",
				funcs, MAX_PLAYER_TEXT_DRAWS, playerid, textid, file.c_str(), Plugin_Settings::line);
			break;

		case LogType::FIND_GLOBAL_TEXT:
			sampgdk::logprintf("[textdraw.streamer] %s: No such id was found. (textId: %d) (%s:%d)",
				funcs, textid, file.c_str(), Plugin_Settings::line);
			break;

		case LogType::SHOW_LIMIT_GLOBAL:
			sampgdk::logprintf("[textdraw.streamer] %s: A maximum of %d global textdraws can be created. (textId: %d) (%s:%d)",
				funcs, MAX_TEXT_DRAWS, textid, file.c_str(), Plugin_Settings::line);
			break;

		case LogType::INVALID_TYPE:
			sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid. (%s:%d)",
				funcs, file.c_str(), Plugin_Settings::line);
			break;
	}
}
