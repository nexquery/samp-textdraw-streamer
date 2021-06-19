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

#include "SlotManager.h"

std::map<int, std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>> SlotManager::Slot;
std::map<int, size_t> SlotManager::Slot_Counter;

size_t SlotManager::Free_ID(size_t playerid)
{
	int id = Start_ID;
	if (Slot[playerid].empty())
	{
		id = Slot_Counter[playerid]++;
	}
	else
	{
		id = Slot[playerid].top();
		Slot[playerid].pop();
	}
	return id;
}

void SlotManager::Remove_ID(size_t playerid, size_t id)
{
	Slot[playerid].push(id);
}

void SlotManager::Reset_ID(size_t playerid)
{
	Slot_Counter[playerid] = Start_ID;
	Slot[playerid] = std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>();
}

void SlotManager::Reset_All_ID()
{
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		Slot_Counter[i] = Start_ID;
		Slot[i] = std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>();
	}
}