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

#include "precompiler.h"

struct PlayerTextDefault
{
	float lettersize_x = 0.0;
	float lettersize_y = 0.0;

	float textsize_x = 0.0;
	float textsize_y = 0.0;

	int alignment = 1;
	int color = -2;
	int usebox = 0;
	int boxcolor = -2;
	int shadow = 2;
	int outline = 0;
	int backgroundcolor = -2;
	int font = 1;
	int proportional = 1;
	int selectable = 0;

	std::string setstring;

	int modelindex = 0;
	float fRotX = 0.0;
	float fRotY = 0.0;
	float fRotZ = 0.0;
	float fZoom = 1.0;

	int veh_col1 = -2;
	int veh_col2 = -2;
};

struct PlayerText
{
	int real_id;

	float create_x;
	float create_y;

	std::string text;

	float lettersize_x;
	float lettersize_y;

	float textsize_x;
	float textsize_y;

	int alignment;
	int color;
	int usebox;
	int boxcolor;
	int shadow;
	int outline;
	int backgroundcolor;
	int font;
	int proportional;
	int selectable;

	std::string setstring;

	int modelindex;
	float fRotX;
	float fRotY;
	float fRotZ;
	float fZoom;

	int veh_col1;
	int veh_col2;
};

class Item
{
public:
	static void Reset();
	static std::unordered_map<int, std::unordered_map<int, std::unique_ptr<PlayerText>>> pText;
	static PlayerTextDefault def_pText;

private:

};