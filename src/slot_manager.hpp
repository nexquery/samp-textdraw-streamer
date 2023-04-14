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

#include <map>
#include <queue>

class slot_manager_player
{
public:
	static int get_id(int playerid);
	static void remove_id(int playerid, int value);
	static void reset_id(int playerid);

private:
	static std::map<int, int> next_Id;
	static std::map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>> p_Ids;
};

class slot_manager_global
{
public:
	static int get_id();
	static void remove_id(int value);
private:
	static int next_Id;
	static std::priority_queue<int, std::vector<int>, std::greater<int>> global_ids;
};