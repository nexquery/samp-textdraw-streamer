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

#include "slot_manager.hpp"

std::map<int, int> slot_manager::next_Id;
std::map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>> slot_manager::p_Ids;

int slot_manager::get_id(int playerid)
{
	if (p_Ids[playerid].empty()) {
		return 1 + next_Id[playerid]++;
	}

	int low_id = p_Ids[playerid].top();
	p_Ids[playerid].pop();

	return low_id;
}

void slot_manager::remove_id(int playerid, int value)
{
	p_Ids[playerid].push(value);
}

void slot_manager::reset_id(int playerid)
{
	next_Id[playerid] = 0;
	p_Ids[playerid] = std::priority_queue<int, std::vector<int>, std::greater<int>>();
}