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

#include "slot_manager.hpp"

 /***
  *     .d8888b.  888          888               888
  *    d88P  Y88b 888          888               888
  *    888    888 888          888               888
  *    888        888  .d88b.  88888b.   8888b.  888
  *    888  88888 888 d88""88b 888 "88b     "88b 888
  *    888    888 888 888  888 888  888 .d888888 888
  *    Y88b  d88P 888 Y88..88P 888 d88P 888  888 888
  *     "Y8888P88 888  "Y88P"  88888P"  "Y888888 888
  *
  */

int slot_manager_global::next_Id;
std::priority_queue<int, std::vector<int>, std::greater<int>> slot_manager_global::global_ids;

int slot_manager_global::get_id()
{
	if (slot_manager_global::global_ids.empty()) {
		return 1 + slot_manager_global::next_Id++;
	}

	int low_id = slot_manager_global::global_ids.top();
	slot_manager_global::global_ids.pop();
	
	return low_id;
}

void slot_manager_global::remove_id(int value)
{
	slot_manager_global::global_ids.push(value);
}


 /***
  *    8888888b.  888
  *    888   Y88b 888
  *    888    888 888
  *    888   d88P 888  8888b.  888  888  .d88b.  888d888
  *    8888888P"  888     "88b 888  888 d8P  Y8b 888P"
  *    888        888 .d888888 888  888 88888888 888
  *    888        888 888  888 Y88b 888 Y8b.     888
  *    888        888 "Y888888  "Y88888  "Y8888  888
  *                                 888
  *                            Y8b d88P
  *                             "Y88P"
  */

std::map<int, int> slot_manager_player::next_Id;
std::map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>> slot_manager_player::p_Ids;

int slot_manager_player::get_id(int playerid)
{
	if (slot_manager_player::p_Ids[playerid].empty()) {
		return 1 + slot_manager_player::next_Id[playerid]++;
	}

	int low_id = slot_manager_player::p_Ids[playerid].top();
	slot_manager_player::p_Ids[playerid].pop();

	return low_id;
}

void slot_manager_player::remove_id(int playerid, int value)
{
	slot_manager_player::p_Ids[playerid].push(value);
}

void slot_manager_player::reset_id(int playerid)
{
	slot_manager_player::next_Id[playerid] = 0;
	slot_manager_player::p_Ids[playerid] = std::priority_queue<int, std::vector<int>, std::greater<int>>();
}