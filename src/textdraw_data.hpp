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

#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sampgdk.hpp"

#define	INVALID_DYNAMIC_PLAYER_TEXTDRAW	(-1)

enum TDStreamer_Type
{
	GLOBAL = 0,
	PLAYER
};

enum LogType
{
	// Player
	CREATE_PLAYER_TEXTDRAW,
	FIND_PLAYER_TEXT,
	SHOW_LIMIT_PLAYER,

	// Global
	FIND_GLOBAL_TEXT,
	SHOW_LIMIT_GLOBAL,

	// Data
	INVALID_TYPE,
};

// The member initializers below are the single source of truth for a new
// textdraw's state. A default-constructed Text_Data doubles as the baseline that
// Reload compares against to skip setter calls that would be no-ops.
struct Text_Data
{
	int					real_id			= INVALID_DYNAMIC_PLAYER_TEXTDRAW;
	float				create_x		= 0.0f;
	float				create_y		= 0.0f;
	std::string			text;
	float				lettersize_x	= 0.0f;
	float				lettersize_y	= 0.0f;
	float				textsize_x		= 0.0f;
	float				textsize_y		= 0.0f;
	int					alignment		= 1;
	int					color			= -2;
	int					usebox			= 0;
	int					boxcolor		= -2;
	int					shadow			= 2;
	int					outline			= 0;
	int					backgroundcolor	= -2;
	int					font			= 1;
	int					proportional	= 1;
	int					selectable		= 0;
	int					modelindex		= 0;
	float				fRotX			= 0.0f;
	float				fRotY			= 0.0f;
	float				fRotZ			= 0.0f;
	float				fZoom			= 1.0f;
	int					veh_col1		= -2;
	int					veh_col2		= -2;

	// Whether the script currently wants this on screen. Distinct from real_id,
	// which only says whether a server-side textdraw is presently allocated.
	bool				visible			= false;

	// Script-attached data. Held by value: an empty map and vector cost no
	// allocation, and the great majority of textdraws never touch either.
	float				float_data		= 0.0f;
	std::map<int, int>	extra_id;
	std::vector<int>	array_data;
};

// Node-based, so a Text_Data* handed out by Find stays valid across later
// inserts into the same container.
using TextMap = std::unordered_map<int, Text_Data>;

class Plugin_Settings
{
public:
	static bool	logMode;

	// The __file/__line the include macros pass in. The string is not read out of
	// the AMX unless a message is actually logged, which is the uncommon path.
	static AMX*	amx;
	static cell	fileParam;
	static int	line;

	static void SetContext(AMX* source, cell file, cell lineNumber)
	{
		amx = source;
		fileParam = file;
		line = static_cast<int>(lineNumber);
	}

	// Called when an AMX unloads so a later log can never resolve a stale pointer.
	static void ClearContext(AMX* source)
	{
		if (amx == source) {
			amx = nullptr;
		}
	}

	static void ILogger(LogType type, const char* funcs, int playerid, int textid);
};

class PlayerText
{
public:
	static const Text_Data					Default;
	static std::array<TextMap*, MAX_PLAYERS>	pText;

	// The player's textdraw pool, or nullptr if out of range or none created yet.
	static TextMap*		Pool(int playerid);

	// Pool(), creating it on first use.
	static TextMap*		Ensure(int playerid);

	// Full guard sequence with the same logging the natives used inline.
	// Returns nullptr and logs when the player or the textdraw is not found.
	static Text_Data*	Find(int playerid, int textid, const char* funcs);

	// Creates the server-side textdraw and applies every non-default property.
	// Does not show it; that is the caller's decision. False means the per-player
	// limit was reached, and real_id is left INVALID.
	static bool			Reload(int playerid, Text_Data& data);

	// Destroys the server-side textdraw if one exists and invalidates real_id.
	static void			DestroyReal(int playerid, Text_Data& data);

	static void			Destroy(int playerid);
	static void			DestroyAll();
};

class GlobalText
{
public:
	static const Text_Data									Default;
	static std::unordered_set<int>							PlayerList;
	static TextMap											gText;
	static std::unordered_map<int, std::unordered_set<int>>	gTextVisible;

	// real_id -> textid, so a textdraw click resolves without scanning gText.
	static std::unordered_map<int, int>						realToText;

	static Text_Data*	Find(int textid, const char* funcs);
	static bool			Reload(int textid, Text_Data& data);
	static void			DestroyReal(Text_Data& data);
	static void			Destroy();
};
