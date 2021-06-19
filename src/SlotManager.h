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
#include <queue>

class SlotManager
{
public:

	static size_t Free_ID(size_t playerid);

	static void Remove_ID(size_t playerid, size_t id);

	static void Reset_ID(size_t playerid);

	static void Reset_All_ID();

private:
	static std::map<int, std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>> Slot;
	static std::map<int, size_t> Slot_Counter;
	static const size_t Start_ID = 1;
};