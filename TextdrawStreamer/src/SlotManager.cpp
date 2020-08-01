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

std::map<int, std::vector<int>> SlotManager::Slot;

size_t SlotManager::Free_ID(size_t playerid)
{
	if (Slot[playerid].empty()) return 1;

	std::sort(Slot[playerid].begin(), Slot[playerid].end());

	size_t sira = 1;

	for (std::vector<int>::iterator it = Slot[playerid].begin(); it != Slot[playerid].end(); ++it)
	{
		if (*it != sira) return sira;
		++sira;
	}
	return sira;
}

void SlotManager::Add_ID(size_t playerid, size_t id)
{
	Slot[playerid].push_back(id);
}

void SlotManager::Remove_ID(size_t playerid, size_t id)
{
	auto sonuc = std::find(Slot[playerid].begin(), Slot[playerid].end(), id);
	if (sonuc != Slot[playerid].end())
	{
		if (LOG_MODE)
		{
			sampgdk::logprintf("%s ID[%d]: %d kaldirildi.", LOG, playerid, id);
		}
		Slot[playerid].erase(sonuc);
	}
}

void SlotManager::Reset_ID(size_t playerid)
{
	if (LOG_MODE)
	{
		sampgdk::logprintf("%s ID: %d resetlendi.", LOG, playerid);
	}
	Slot[playerid].clear();
}

void SlotManager::Reset_All_ID()
{
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		Slot[i].clear();
	}
}