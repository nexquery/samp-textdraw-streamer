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

#include "amx/amx.h"

#ifndef _INCLUDE_FORMATTING_H
#define _INCLUDE_FORMATTING_H

 //Amx Templatized Cell Printf
template <typename D, typename S>
size_t atcprintf(D* buffer, size_t maxlen, const S* format, AMX* amx, cell* params, int* param);

#endif //_INCLUDE_FORMATTING_H