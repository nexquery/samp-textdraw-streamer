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

#if defined _INC_textdraw_streamer
	#endinput
#endif
#define _INC_textdraw_streamer

/***
 *    888                       
 *    888                       
 *    888                       
 *    888      .d88b.   .d88b.  
 *    888     d88""88b d88P"88b 
 *    888     888  888 888  888 
 *    888     Y88..88P Y88b 888 
 *    88888888 "Y88P"   "Y88888 
 *                          888 
 *                     Y8b d88P 
 *                      "Y88P"  
 */

public TDS_Enable_Log = true;
#pragma unused TDS_Enable_Log

/***
 *    88888888888                         
 *        888                             
 *        888                             
 *        888  888  888 88888b.   .d88b.  
 *        888  888  888 888 "88b d8P  Y8b 
 *        888  888  888 888  888 88888888 
 *        888  Y88b 888 888 d88P Y8b.     
 *        888   "Y88888 88888P"   "Y8888  
 *                  888 888               
 *             Y8b d88P 888               
 *              "Y88P"  888               
 */

#define	DYNAMIC_TEXTDRAW_TYPE_GLOBAL (DYNAMIC_TEXTDRAW_TYPE:0)
#define	DYNAMIC_TEXTDRAW_TYPE_PLAYER (DYNAMIC_TEXTDRAW_TYPE:1)

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

// General
native Text:CreateDynamicTextDraw(Float:x, Float:y, const format[], {Float, _}:...);
native DestroyDynamicTextDraw(Text:textid);
native DynamicTextDrawLetterSize(Text:textid, Float:width, Float:height);
native DynamicTextDrawTextSize(Text:textid, Float:width, Float:height);
native DynamicTextDrawAlignment(Text:textid, alignment);
native DynamicTextDrawColour(Text:textid, textColour);
native DynamicTextDrawUseBox(Text:textid, enableBox);
native DynamicTextDrawBoxColour(Text:textid, boxColour);
native DynamicTextDrawSetShadow(Text:textid, shadowSize);
native DynamicTextDrawSetOutline(Text:textid, outlineSize);
native DynamicTextDrawBackgroundColour(Text:textid, backgroundColour);
native DynamicTextDrawFont(Text:textid, font);
native DynamicTextDrawSetProportional(Text:textid, proportional);
native DynamicTextDrawSetSelectable(Text:textid, selectable);
native DynamicTextDrawShowForPlayer(playerid, Text:textid);
native DynamicTextDrawHideForPlayer(playerid, Text:textid);
native DynamicTextDrawShowForAll(Text:textid);
native DynamicTextDrawHideForAll(Text:textid);
native DynamicTextDrawSetString(Text:textid, const format[], {Float, _}:...);
native DynamicTextDrawSetPreviewModel(Text:textid, model);
native DynamicTextDrawSetPreviewRot(Text:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0);
native DynamicTextDrawSetPreviewVehCol(Text:textid, colour1, colour2);

// YSF Functions (names changed to avoid open.mp conflicts)
native IsValidDynamicTextDraw(Text:textid);
native IsDynTextDrawVisibleForPlayer(playerid, Text:textid);
native DynamicTextDrawGetString(Text:textid, string[], stringSize = sizeof(string));
native DynamicTextDrawSetPos(Text:textid, Float:x, Float:y);
native DynamicTextDrawGetLetterSize(Text:textid, &Float:width, &Float:height);
native DynamicTextDrawGetTextSize(Text:textid, &Float:width, &Float:height);
native DynamicTextDrawGetPos(Text:textid, &Float:x, &Float:y);
native DynamicTextDrawGetColour(Text:textid);
native DynamicTextDrawGetBoxColour(Text:textid);
native DynamicTextDrawGetBackgroundCol(Text:textid);
native DynamicTextDrawGetShadow(Text:textid);
native DynamicTextDrawGetOutline(Text:textid);
native DynamicTextDrawGetFont(Text:textid);
native DynamicTextDrawIsBox(Text:textid);
native DynamicTextDrawIsProportional(Text:textid);
native DynamicTextDrawIsSelectable(Text:textid);
native DynamicTextDrawGetAlignment(Text:textid);
native DynamicTextDrawGetPreviewModel(Text:textid);
native DynamicTextDrawGetPreviewRot(Text:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom);
native DynamicTextDrawGetPreviewVehCol(Text:textid, &colour1, &colour2);

// Get the real textdraw id shown
native DynamicTextDrawGetRealID(Text:textid, &Text:realid);

// Get the total number of textdraws
native DynamicTextDrawGetSize();

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

// General
native PlayerText:CreateDynamicPlayerTextDraw(playerid, Float:x, Float:y, const format[], {Float, _}:...);
native DestroyDynamicPlayerTextDraw(playerid, PlayerText:textid);
native DynamicPlayerTextDrawLetterSize(playerid, PlayerText:textid, Float:width, Float:height);
native DynamicPlayerTextDrawTextSize(playerid, PlayerText:textid, Float:width, Float:height);
native DynamicPlayerTextDrawAlignment(playerid, PlayerText:textid, alignment);
native DynamicPlayerTextDrawColour(playerid, PlayerText:textid, textColour);
native DynamicPlayerTextDrawUseBox(playerid, PlayerText:textid, enableBox);
native DynamicPlayerTextDrawBoxColor(playerid, PlayerText:textid, boxColour);
native DynamicPlayerTextDrawSetShadow(playerid, PlayerText:textid, shadowSize);
native DynamicPlayerTextDrawSetOutline(playerid, PlayerText:textid, outlineSize);
native DynamicPlayerTextDrawBGColour(playerid, PlayerText:textid, backgroundColour);
native DynamicPlayerTextDrawFont(playerid, PlayerText:textid, font);
native DynPlayerTextSetProportional(playerid, PlayerText:textid, proportional);
native DynamicPlayerTextDrawSelectable(playerid, PlayerText:textid, selectable);
native DynamicPlayerTextDrawShow(playerid, PlayerText:textid);
native DynamicPlayerTextDrawHide(playerid, PlayerText:textid);
native DynamicPlayerTextDrawSetString(playerid, PlayerText:textid, const format[], {Float, _}:...);
native DynamicPlayerTextDrawSetPrevMdl(playerid, PlayerText:textid, model);
native DynamicPlayerTextDrawSetPrevRot(playerid, PlayerText:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0);
native DynamicPlayerTextDrawPrevVehCol(playerid, PlayerText:textid, colour1, colour2);

// YSF Functions (names changed to avoid open.mp conflicts)
native IsValidDynamicPlayerTextDraw(playerid, PlayerText:textid);
native IsDynamicPlayerTextDrawVisible(playerid, PlayerText:textid);
native DynamicPlayerTextDrawGetString(playerid, PlayerText:textid, string[], stringSize = sizeof(string));
native DynamicPlayerTextDrawSetPos(playerid, PlayerText:textid, Float:x, Float:y);
native DynPlayerTextDrawGetLetterSize(playerid, PlayerText:textid, &Float:width, &Float:height);
native DynPlayerTextDrawGetTextSize(playerid, PlayerText:textid, &Float:width, &Float:height);
native DynamicPlayerTextDrawGetPos(playerid, PlayerText:textid, &Float:x, &Float:y);
native DynamicPlayerTextDrawGetColour(playerid, PlayerText:textid);
native DynamicPlayerTextDrawGetBoxCol(playerid, PlayerText:textid);
native DynPlayerTextDrawGetBGColour(playerid, PlayerText:textid);
native DynamicPlayerTextDrawGetShadow(playerid, PlayerText:textid);
native DynamicPlayerTextDrawGetOutline(playerid, PlayerText:textid);
native DynamicPlayerTextDrawGetFont(playerid, PlayerText:textid);
native DynamicPlayerTextDrawIsBox(playerid, PlayerText:textid);
native DynPlayerTextDrawIsProportional(playerid, PlayerText:textid);
native DynPlayerTextDrawIsSelectable(playerid, PlayerText:textid);
native DynPlayerTextDrawGetAlignment(playerid, PlayerText:textid);
native DynPlayerTextDrawGetPreviewMdl(playerid, PlayerText:textid);
native DynPlayerTextDrawGetPreviewRot(playerid, PlayerText:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom);
native DynPlayerTextDrawGetPrevVehCol(playerid, PlayerText:textid, &colour1, &colour2);

// Get the real textdraw id shown
native PlayerTextDrawGetRealID(playerid, PlayerText:text, &PlayerText:realid);

// Total number of textdraws created for the player
native PlayerTextDrawGetSize(playerid);

/***
 *    8888888b.           888             
 *    888  "Y88b          888             
 *    888    888          888             
 *    888    888  8888b.  888888  8888b.  
 *    888    888     "88b 888        "88b 
 *    888    888 .d888888 888    .d888888 
 *    888  .d88P 888  888 Y88b.  888  888 
 *    8888888P"  "Y888888  "Y888 "Y888888 
 *
 */

// Int
native DynamicTextDraw_SetIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, index, value, playerid = -1);
native DynamicTextDraw_GetIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, index, playerid = -1);
native DynamicTextDraw_ClearIntData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);

// Float
native DynamicTextDraw_SetFloatData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, Float:value, playerid = -1);
native Float:DynamicTextDraw_GetFloatData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);

// Array
native DynamicTextDraw_SetArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, const src[], playerid = -1, maxSrc = sizeof(src));
native DynamicTextDraw_GetArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, const dest[], playerid = -1, maxDest = sizeof(dest));
native DynamicTextDraw_ClearArrayData(DYNAMIC_TEXTDRAW_TYPE:type, {Text, PlayerText}:textid, playerid = -1);

/***
 *     .d8888b.           888 888 888                        888               
 *    d88P  Y88b          888 888 888                        888               
 *    888    888          888 888 888                        888               
 *    888         8888b.  888 888 88888b.   8888b.   .d8888b 888  888 .d8888b  
 *    888            "88b 888 888 888 "88b     "88b d88P"    888 .88P 88K      
 *    888    888 .d888888 888 888 888  888 .d888888 888      888888K  "Y8888b. 
 *    Y88b  d88P 888  888 888 888 888 d88P 888  888 Y88b.    888 "88b      X88 
 *     "Y8888P"  "Y888888 888 888 88888P"  "Y888888  "Y8888P 888  888  88888P' 
 *
 */

// It will be called when the Escape (ESC) key is pressed
forward OnCancelDynamicTextDraw(playerid);

// Globally created textdraw will be called if clicks
forward OnClickDynamicTextDraw(playerid, Text:textid);

// The textdraw created for the player will be called if they click
forward OnClickDynamicPlayerTextDraw(playerid, PlayerText:textid);

/***
 *    888    888                   888                                 .d8888b.  888          888               888 
 *    888    888                   888                                d88P  Y88b 888          888               888 
 *    888    888                   888                                888    888 888          888               888 
 *    8888888888  .d88b.   .d88b.  888  888 .d8888b                   888        888  .d88b.  88888b.   8888b.  888 
 *    888    888 d88""88b d88""88b 888 .88P 88K                       888  88888 888 d88""88b 888 "88b     "88b 888 
 *    888    888 888  888 888  888 888888K  "Y8888b.      888888      888    888 888 888  888 888  888 .d888888 888 
 *    888    888 Y88..88P Y88..88P 888 "88b      X88                  Y88b  d88P 888 Y88..88P 888 d88P 888  888 888 
 *    888    888  "Y88P"   "Y88P"  888  888  88888P'                   "Y8888P88 888  "Y88P"  88888P"  "Y888888 888 
 *                                                                                                                  
 */

/*******************************************************************************/
#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif
#define TextDrawCreate CreateDynamicTextDraw
/*******************************************************************************/
#if defined _ALS_TextDrawDestroy
	#undef TextDrawDestroy
#else
	#define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy DestroyDynamicTextDraw
/*******************************************************************************/
#if defined _ALS_TextDrawLetterSize
	#undef TextDrawLetterSize
#else
	#define _ALS_TextDrawLetterSize
#endif
#define TextDrawLetterSize DynamicTextDrawLetterSize
/*******************************************************************************/
#if defined _ALS_TextDrawTextSize
	#undef TextDrawTextSize
#else
	#define _ALS_TextDrawTextSize
#endif
#define TextDrawTextSize DynamicTextDrawTextSize
/*******************************************************************************/
#if defined _ALS_TextDrawAlignment
	#undef TextDrawAlignment
#else
	#define _ALS_TextDrawAlignment
#endif
#define TextDrawAlignment DynamicTextDrawAlignment
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawColour
		#undef TextDrawColour
	#else
		#define _ALS_TextDrawColour
	#endif
	#define TextDrawColour DynamicTextDrawColour
#else
	#if defined _ALS_TextDrawColor
		#undef TextDrawColor
	#else
		#define _ALS_TextDrawColor
	#endif
	#define TextDrawColor DynamicTextDrawColour
#endif
/*******************************************************************************/
#if defined _ALS_TextDrawUseBox
	#undef TextDrawUseBox
#else
	#define _ALS_TextDrawUseBox
#endif
#define TextDrawUseBox DynamicTextDrawUseBox
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawBoxColour
		#undef TextDrawBoxColour
	#else
		#define _ALS_TextDrawBoxColour
	#endif
	#define TextDrawBoxColour DynamicTextDrawBoxColour
#else
	#if defined _ALS_TextDrawBoxColor
		#undef TextDrawBoxColor
	#else
		#define _ALS_TextDrawBoxColor
	#endif
	#define TextDrawBoxColor DynamicTextDrawBoxColour
#endif
/*******************************************************************************/
#if defined _ALS_TextDrawSetShadow
	#undef TextDrawSetShadow
#else
	#define _ALS_TextDrawSetShadow
#endif
#define TextDrawSetShadow DynamicTextDrawSetShadow
/*******************************************************************************/
#if defined _ALS_TextDrawSetOutline
	#undef TextDrawSetOutline
#else
	#define _ALS_TextDrawSetOutline
#endif
#define TextDrawSetOutline DynamicTextDrawSetOutline
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawBackgroundColour
		#undef TextDrawBackgroundColour
	#else
		#define _ALS_TextDrawBackgroundColour
	#endif
	#define TextDrawBackgroundColour DynamicTextDrawBackgroundColour
#else
	#if defined _ALS_TextDrawBackgroundColor
		#undef TextDrawBackgroundColor
	#else
		#define _ALS_TextDrawBackgroundColor
	#endif
	#define TextDrawBackgroundColor DynamicTextDrawBackgroundColour
#endif
/*******************************************************************************/
#if defined _ALS_TextDrawFont
	#undef TextDrawFont
#else
	#define _ALS_TextDrawFont
#endif
#define TextDrawFont DynamicTextDrawFont
/*******************************************************************************/
#if defined _ALS_TextDrawSetProportional
	#undef TextDrawSetProportional
#else
	#define _ALS_TextDrawSetProportional
#endif
#define TextDrawSetProportional DynamicTextDrawSetProportional
/*******************************************************************************/
#if defined _ALS_TextDrawSetSelectable
	#undef TextDrawSetSelectable
#else
	#define _ALS_TextDrawSetSelectable
#endif
#define TextDrawSetSelectable DynamicTextDrawSetSelectable
/*******************************************************************************/
#if defined _ALS_TextDrawShowForPlayer
	#undef TextDrawShowForPlayer
#else
	#define _ALS_TextDrawShowForPlayer
#endif
#define TextDrawShowForPlayer DynamicTextDrawShowForPlayer
/*******************************************************************************/
#if defined _ALS_TextDrawHideForPlayer
	#undef TextDrawHideForPlayer
#else
	#define _ALS_TextDrawHideForPlayer
#endif
#define TextDrawHideForPlayer DynamicTextDrawHideForPlayer
/*******************************************************************************/
#if defined _ALS_TextDrawShowForAll
	#undef TextDrawShowForAll
#else
	#define _ALS_TextDrawShowForAll
#endif
#define TextDrawShowForAll DynamicTextDrawShowForAll
/*******************************************************************************/
#if defined _ALS_TextDrawHideForAll
	#undef TextDrawHideForAll
#else
	#define _ALS_TextDrawHideForAll
#endif
#define TextDrawHideForAll DynamicTextDrawHideForAll
/*******************************************************************************/
#if defined _ALS_TextDrawSetString
	#undef TextDrawSetString
#else
	#define _ALS_TextDrawSetString
#endif
#define TextDrawSetString DynamicTextDrawSetString
/*******************************************************************************/
#if defined _ALS_TextDrawSetPreviewModel
	#undef TextDrawSetPreviewModel
#else
	#define _ALS_TextDrawSetPreviewModel
#endif
#define TextDrawSetPreviewModel DynamicTextDrawSetPreviewModel
/*******************************************************************************/
#if defined _ALS_TextDrawSetPreviewRot
	#undef TextDrawSetPreviewRot
#else
	#define _ALS_TextDrawSetPreviewRot
#endif
#define TextDrawSetPreviewRot DynamicTextDrawSetPreviewRot
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawSetPreviewVehicleColours
		#undef TextDrawSetPreviewVehicleColours
	#else
		#define _ALS_TextDrawSetPreviewVehicleColours
	#endif
	#define TextDrawSetPreviewVehicleColours DynamicTextDrawSetPreviewVehCol
#else
	#if defined _ALS_TextDrawSetPreviewVehCol
		#undef TextDrawSetPreviewVehCol
	#else
		#define _ALS_TextDrawSetPreviewVehCol
	#endif
	#define TextDrawSetPreviewVehCol DynamicTextDrawSetPreviewVehCol
#endif
/*******************************************************************************/

/***
 *    888    888                   888                                8888888b.  888                                    
 *    888    888                   888                                888   Y88b 888                                    
 *    888    888                   888                                888    888 888                                    
 *    8888888888  .d88b.   .d88b.  888  888 .d8888b                   888   d88P 888  8888b.  888  888  .d88b.  888d888 
 *    888    888 d88""88b d88""88b 888 .88P 88K                       8888888P"  888     "88b 888  888 d8P  Y8b 888P"   
 *    888    888 888  888 888  888 888888K  "Y8888b.      888888      888        888 .d888888 888  888 88888888 888     
 *    888    888 Y88..88P Y88..88P 888 "88b      X88                  888        888 888  888 Y88b 888 Y8b.     888     
 *    888    888  "Y88P"   "Y88P"  888  888  88888P'                  888        888 "Y888888  "Y88888  "Y8888  888     
 *                                                                                                 888                  
 *                                                                                            Y8b d88P                  
 *                                                                                             "Y88P"                   
 */

/*******************************************************************************/
#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw CreateDynamicPlayerTextDraw
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawDestroy
	#undef PlayerTextDrawDestroy
#else
	#define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy DestroyDynamicPlayerTextDraw
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawLetterSize
	#undef PlayerTextDrawLetterSize
#else
	#define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize DynamicPlayerTextDrawLetterSize
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawTextSize
	#undef PlayerTextDrawTextSize
#else
	#define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize DynamicPlayerTextDrawTextSize
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawAlignment
	#undef PlayerTextDrawAlignment
#else
	#define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment DynamicPlayerTextDrawAlignment
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawColour
		#undef PlayerTextDrawColour
	#else
		#define _ALS_PlayerTextDrawColour
	#endif
	#define PlayerTextDrawColour DynamicPlayerTextDrawColour
#else
	#if defined _ALS_PlayerTextDrawColor
		#undef PlayerTextDrawColor
	#else
		#define _ALS_PlayerTextDrawColor
	#endif
	#define PlayerTextDrawColor DynamicPlayerTextDrawColour
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawUseBox
	#undef PlayerTextDrawUseBox
#else
	#define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox DynamicPlayerTextDrawUseBox
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawBoxColour
		#undef PlayerTextDrawBoxColour
	#else
		#define _ALS_PlayerTextDrawBoxColour
	#endif
	#define PlayerTextDrawBoxColour DynamicPlayerTextDrawBoxColor
#else
	#if defined _ALS_PlayerTextDrawBoxColor
		#undef PlayerTextDrawBoxColor
	#else
		#define _ALS_PlayerTextDrawBoxColor
	#endif
	#define PlayerTextDrawBoxColor DynamicPlayerTextDrawBoxColor
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetShadow
	#undef PlayerTextDrawSetShadow
#else
	#define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow DynamicPlayerTextDrawSetShadow
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetOutline
	#undef PlayerTextDrawSetOutline
#else
	#define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline DynamicPlayerTextDrawSetOutline
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawBackgroundCo
		#undef PlayerTextDrawBackgroundColour
	#else
		#define _ALS_PlayerTextDrawBackgroundCo
	#endif
	#define PlayerTextDrawBackgroundColour DynamicPlayerTextDrawBGColour
#else
	#if defined _ALS_PlayerTextDrawBackgroundCo
		#undef PlayerTextDrawBackgroundColor
	#else
		#define _ALS_PlayerTextDrawBackgroundCo
	#endif
	#define PlayerTextDrawBackgroundColor DynamicPlayerTextDrawBGColour
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawFont
	#undef PlayerTextDrawFont
#else
	#define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont DynamicPlayerTextDrawFont
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawSetProportional
		#undef PlayerTextDrawSetProportional
	#else
		#define _ALS_PlayerTextDrawSetProportional
	#endif
	#define PlayerTextDrawSetProportional DynPlayerTextSetProportional
#else
	#if defined _ALS_PlayerTextDrawSetProportio
		#undef PlayerTextDrawSetProportional
	#else
		#define _ALS_PlayerTextDrawSetProportio
	#endif
	#define PlayerTextDrawSetProportional DynPlayerTextSetProportional
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetSelectabl
	#undef PlayerTextDrawSetSelectable
#else
	#define _ALS_PlayerTextDrawSetSelectabl
#endif
#define PlayerTextDrawSetSelectable DynamicPlayerTextDrawSelectable
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawShow
	#undef PlayerTextDrawShow
#else
	#define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow DynamicPlayerTextDrawShow
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawHide
	#undef PlayerTextDrawHide
#else
	#define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide DynamicPlayerTextDrawHide
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString DynamicPlayerTextDrawSetString
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetPreviewMo
	#undef PlayerTextDrawSetPreviewModel
#else
	#define _ALS_PlayerTextDrawSetPreviewMo
#endif
#define PlayerTextDrawSetPreviewModel DynamicPlayerTextDrawSetPrevMdl
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetPreviewRo
	#undef PlayerTextDrawSetPreviewRot
#else
	#define _ALS_PlayerTextDrawSetPreviewRo
#endif
#define PlayerTextDrawSetPreviewRot DynamicPlayerTextDrawSetPrevRot
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawSetPreviewVehicleColours
		#undef PlayerTextDrawSetPreviewVehicleColours
	#else
		#define _ALS_PlayerTextDrawSetPreviewVehicleColours
	#endif
	#define PlayerTextDrawSetPreviewVehicleColours DynamicPlayerTextDrawPrevVehCol
#else
	#if defined _ALS_PlayerTextDrawSetPreviewVe
		#undef PlayerTextDrawSetPreviewVehCol
	#else
		#define _ALS_PlayerTextDrawSetPreviewVe
	#endif
	#define PlayerTextDrawSetPreviewVehCol DynamicPlayerTextDrawPrevVehCol
#endif
/*******************************************************************************/