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
native DestroyDynamicTextDraw(Text:textid, const file[], line);
native DynamicTextDrawLetterSize(Text:textid, Float:width, Float:height, const file[], line);
native DynamicTextDrawTextSize(Text:textid, Float:width, Float:height, const file[], line);
native DynamicTextDrawAlignment(Text:textid, alignment, const file[], line);
native DynamicTextDrawColour(Text:textid, textColour, const file[], line);
native DynamicTextDrawUseBox(Text:textid, enableBox, const file[], line);
native DynamicTextDrawBoxColour(Text:textid, boxColour, const file[], line);
native DynamicTextDrawSetShadow(Text:textid, shadowSize, const file[], line);
native DynamicTextDrawSetOutline(Text:textid, outlineSize, const file[], line);
native DynamicTextDrawBackgroundColour(Text:textid, backgroundColour, const file[], line);
native DynamicTextDrawFont(Text:textid, font, const file[], line);
native DynamicTextDrawSetProportional(Text:textid, proportional, const file[], line);
native DynamicTextDrawSetSelectable(Text:textid, selectable, const file[], line);
native DynamicTextDrawShowForPlayer(playerid, Text:textid, const file[], line);
native DynamicTextDrawHideForPlayer(playerid, Text:textid, const file[], line);
native DynamicTextDrawShowForAll(Text:textid, const file[], line);
native DynamicTextDrawHideForAll(Text:textid, const file[], line);
native DynamicTextDrawSetString(Text:textid, const format[], {Float, _}:...);
native DynamicTextDrawSetPreviewModel(Text:textid, model, const file[], line);
native DynamicTextDrawSetPreviewRot(Text:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0, const file[], line);
native DynamicTextDrawSetPreviewVehCol(Text:textid, colour1, colour2, const file[], line);

// YSF Functions (names changed to avoid open.mp conflicts)
native IsValidDynamicTextDraw(Text:textid);
native IsDynTextDrawVisibleForPlayer_(playerid, Text:textid, const file[], line) = IsDynTextDrawVisibleForPlayer;
native DynamicTextDrawGetString(Text:textid, string[], stringSize = sizeof(string));
native DynamicTextDrawSetPos_(Text:textid, Float:x, Float:y, const file[], line) = DynamicTextDrawSetPos;
native DynamicTextDrawGetLetterSize_(Text:textid, &Float:width, &Float:height, const file[], line) = DynamicTextDrawGetLetterSize;
native DynamicTextDrawGetTextSize_(Text:textid, &Float:width, &Float:height, const file[], line) = DynamicTextDrawGetTextSize;
native DynamicTextDrawGetPos_(Text:textid, &Float:x, &Float:y, const file[], line) = DynamicTextDrawGetPos;
native DynamicTextDrawGetColour_(Text:textid, const file[], line) = DynamicTextDrawGetColour;
native DynamicTextDrawGetBoxColour_(Text:textid, const file[], line) = DynamicTextDrawGetBoxColour;
native DynamicTextDrawGetBackgroundCo(Text:textid, const file[], line);
native DynamicTextDrawGetShadow_(Text:textid, const file[], line) = DynamicTextDrawGetShadow;
native DynamicTextDrawGetOutline_(Text:textid, const file[], line) = DynamicTextDrawGetOutline;
native DynamicTextDrawGetFont_(Text:textid, const file[], line) = DynamicTextDrawGetFont;
native DynamicTextDrawIsBox_(Text:textid, const file[], line) = DynamicTextDrawIsBox;
native DynamicTextDrawIsProportional_(Text:textid, const file[], line) = DynamicTextDrawIsProportional;
native DynamicTextDrawIsSelectable_(Text:textid, const file[], line) = DynamicTextDrawIsSelectable;
native DynamicTextDrawGetAlignment_(Text:textid, const file[], line) = DynamicTextDrawGetAlignment;
native DynamicTextDrawGetPreviewModel_(Text:textid, const file[], line) = DynamicTextDrawGetPreviewModel;
native DynamicTextDrawGetPreviewRot_(Text:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom, const file[], line) = DynamicTextDrawGetPreviewRot;
native DynamicTextDrawGetPreviewVehCo(Text:textid, &colour1, &colour2, const file[], line);

// Get the real textdraw id shown
native DynamicTextDrawGetRealID_(Text:textid, &Text:realid, const file[], line) = DynamicTextDrawGetRealID;

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
native DestroyDynamicPlayerTextDraw(playerid, PlayerText:textid, const file[], line);
native DynamicPlayerTextDrawLetterSize(playerid, PlayerText:textid, Float:width, Float:height, const file[], line);
native DynamicPlayerTextDrawTextSize(playerid, PlayerText:textid, Float:width, Float:height, const file[], line);
native DynamicPlayerTextDrawAlignment(playerid, PlayerText:textid, alignment, const file[], line);
native DynamicPlayerTextDrawColour(playerid, PlayerText:textid, textColour, const file[], line);
native DynamicPlayerTextDrawUseBox(playerid, PlayerText:textid, enableBox, const file[], line);
native DynamicPlayerTextDrawBoxColor(playerid, PlayerText:textid, boxColour, const file[], line);
native DynamicPlayerTextDrawSetShadow(playerid, PlayerText:textid, shadowSize, const file[], line);
native DynamicPlayerTextDrawSetOutline(playerid, PlayerText:textid, outlineSize, const file[], line);
native DynamicPlayerTextDrawBGColour(playerid, PlayerText:textid, backgroundColour, const file[], line);
native DynamicPlayerTextDrawFont(playerid, PlayerText:textid, font, const file[], line);
native DynPlayerTextSetProportional(playerid, PlayerText:textid, proportional, const file[], line);
native DynamicPlayerTextDrawSelectable(playerid, PlayerText:textid, selectable, const file[], line);
native DynamicPlayerTextDrawShow(playerid, PlayerText:textid, const file[], line);
native DynamicPlayerTextDrawHide(playerid, PlayerText:textid, const file[], line);
native DynamicPlayerTextDrawSetString(playerid, PlayerText:textid, const format[], {Float, _}:...);
native DynamicPlayerTextDrawSetPrevMdl(playerid, PlayerText:textid, model, const file[], line);
native DynamicPlayerTextDrawSetPrevRot(playerid, PlayerText:textid, Float:rotationX, Float:rotationY, Float:rotationZ, Float:zoom = 1.0, const file[], line);
native DynamicPlayerTextDrawPrevVehCol(playerid, PlayerText:textid, colour1, colour2, const file[], line);

// YSF Functions (names changed to avoid open.mp conflicts)
native IsValidDynamicPlayerTextDraw(playerid, PlayerText:textid);
native IsDynamicPlayerTextDrawVisible_(playerid, PlayerText:textid, const file[], line) = IsDynamicPlayerTextDrawVisible;
native DynamicPlayerTextDrawGetString(playerid, PlayerText:textid, string[], stringSize = sizeof(string));
native DynamicPlayerTextDrawSetPos_(playerid, PlayerText:textid, Float:x, Float:y, const file[], line) = DynamicPlayerTextDrawSetPos;
native DynPlayerTextDrawGetLetterSize_(playerid, PlayerText:textid, &Float:width, &Float:height, const file[], line) = DynPlayerTextDrawGetLetterSize;
native DynPlayerTextDrawGetTextSize_(playerid, PlayerText:textid, &Float:width, &Float:height, const file[], line) = DynPlayerTextDrawGetTextSize;
native DynamicPlayerTextDrawGetPos_(playerid, PlayerText:textid, &Float:x, &Float:y, const file[], line) = DynamicPlayerTextDrawGetPos;
native DynamicPlayerTextDrawGetColour_(playerid, PlayerText:textid, const file[], line) = DynamicPlayerTextDrawGetColour;
native DynamicPlayerTextDrawGetBoxCol_(playerid, PlayerText:textid, const file[], line) = DynamicPlayerTextDrawGetBoxCol;
native DynPlayerTextDrawGetBGColour_(playerid, PlayerText:textid, const file[], line) = DynPlayerTextDrawGetBGColour;
native DynamicPlayerTextDrawGetShadow_(playerid, PlayerText:textid, const file[], line) = DynamicPlayerTextDrawGetShadow;
native DynamicPlayerTextDrawGetOutlin_(playerid, PlayerText:textid, const file[], line) = DynamicPlayerTextDrawGetOutline;
native DynamicPlayerTextDrawGetFont_(playerid, PlayerText:textid, const file[], line) = DynamicPlayerTextDrawGetFont;
native DynamicPlayerTextDrawIsBox_(playerid, PlayerText:textid, const file[], line) = DynamicPlayerTextDrawIsBox;
native DynPlayerTextDrawIsProportiona_(playerid, PlayerText:textid, const file[], line) = DynPlayerTextDrawIsProportional;
native DynPlayerTextDrawIsSelectable_(playerid, PlayerText:textid, const file[], line) = DynPlayerTextDrawIsSelectable;
native DynPlayerTextDrawGetAlignment_(playerid, PlayerText:textid, const file[], line) = DynPlayerTextDrawGetAlignment;
native DynPlayerTextDrawGetPreviewMdl_(playerid, PlayerText:textid, const file[], line) = DynPlayerTextDrawGetPreviewMdl;
native DynPlayerTextDrawGetPreviewRot_(playerid, PlayerText:textid, &Float:rotationX, &Float:rotationY, &Float:rotationZ, &Float:zoom, const file[], line) = DynPlayerTextDrawGetPreviewRot;
native DynPlayerTextDrawGetPrevVehCol_(playerid, PlayerText:textid, &colour1, &colour2, const file[], line) = DynPlayerTextDrawGetPrevVehCol;

// Get the real textdraw id shown
native PlayerTextDrawGetRealID_(playerid, PlayerText:text, &PlayerText:realid, const file[], line) = PlayerTextDrawGetRealID;

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
#define TextDrawDestroy(%0) DestroyDynamicTextDraw(%0, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawLetterSize
	#undef TextDrawLetterSize
#else
	#define _ALS_TextDrawLetterSize
#endif
#define TextDrawLetterSize(%0,%1,%2) DynamicTextDrawLetterSize(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawTextSize
	#undef TextDrawTextSize
#else
	#define _ALS_TextDrawTextSize
#endif
#define TextDrawTextSize(%0,%1,%2) DynamicTextDrawTextSize(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawAlignment
	#undef TextDrawAlignment
#else
	#define _ALS_TextDrawAlignment
#endif
#define TextDrawAlignment(%0,%1) DynamicTextDrawAlignment(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawColour
		#undef TextDrawColour
	#else
		#define _ALS_TextDrawColour
	#endif
	#define TextDrawColour(%0,%1) DynamicTextDrawColour(%0, %1, __file, __line)
#else
	#if defined _ALS_TextDrawColor
		#undef TextDrawColor
	#else
		#define _ALS_TextDrawColor
	#endif
	#define TextDrawColor(%0,%1) DynamicTextDrawColour(%0, %1, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_TextDrawUseBox
	#undef TextDrawUseBox
#else
	#define _ALS_TextDrawUseBox
#endif
#define TextDrawUseBox(%0,%1) DynamicTextDrawUseBox(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawBoxColour
		#undef TextDrawBoxColour
	#else
		#define _ALS_TextDrawBoxColour
	#endif
	#define TextDrawBoxColour(%0,%1) DynamicTextDrawBoxColour(%0, %1, __file, __line)
#else
	#if defined _ALS_TextDrawBoxColor
		#undef TextDrawBoxColor
	#else
		#define _ALS_TextDrawBoxColor
	#endif
	#define TextDrawBoxColor(%0,%1) DynamicTextDrawBoxColour(%0, %1, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_TextDrawSetShadow
	#undef TextDrawSetShadow
#else
	#define _ALS_TextDrawSetShadow
#endif
#define TextDrawSetShadow(%0,%1) DynamicTextDrawSetShadow(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawSetOutline
	#undef TextDrawSetOutline
#else
	#define _ALS_TextDrawSetOutline
#endif
#define TextDrawSetOutline(%0,%1) DynamicTextDrawSetOutline(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawBackgroundColour
		#undef TextDrawBackgroundColour
	#else
		#define _ALS_TextDrawBackgroundColour
	#endif
	#define TextDrawBackgroundColour(%0,%1) DynamicTextDrawBackgroundColour(%0, %1, __file, __line)
#else
	#if defined _ALS_TextDrawBackgroundColor
		#undef TextDrawBackgroundColor
	#else
		#define _ALS_TextDrawBackgroundColor
	#endif
	#define TextDrawBackgroundColor(%0,%1) DynamicTextDrawBackgroundColour(%0, %1, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_TextDrawFont
	#undef TextDrawFont
#else
	#define _ALS_TextDrawFont
#endif
#define TextDrawFont(%0,%1) DynamicTextDrawFont(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawSetProportional
	#undef TextDrawSetProportional
#else
	#define _ALS_TextDrawSetProportional
#endif
#define TextDrawSetProportional(%0,%1) DynamicTextDrawSetProportional(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawSetSelectable
	#undef TextDrawSetSelectable
#else
	#define _ALS_TextDrawSetSelectable
#endif
#define TextDrawSetSelectable(%0,%1) DynamicTextDrawSetSelectable(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawShowForPlayer
	#undef TextDrawShowForPlayer
#else
	#define _ALS_TextDrawShowForPlayer
#endif
#define TextDrawShowForPlayer(%0,%1) DynamicTextDrawShowForPlayer(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawHideForPlayer
	#undef TextDrawHideForPlayer
#else
	#define _ALS_TextDrawHideForPlayer
#endif
#define TextDrawHideForPlayer(%0,%1) DynamicTextDrawHideForPlayer(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawShowForAll
	#undef TextDrawShowForAll
#else
	#define _ALS_TextDrawShowForAll
#endif
#define TextDrawShowForAll(%0) DynamicTextDrawShowForAll(%0, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawHideForAll
	#undef TextDrawHideForAll
#else
	#define _ALS_TextDrawHideForAll
#endif
#define TextDrawHideForAll(%0) DynamicTextDrawHideForAll(%0, __file, __line)
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
#define TextDrawSetPreviewModel(%0,%1) DynamicTextDrawSetPreviewModel(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_TextDrawSetPreviewRot
	#undef TextDrawSetPreviewRot
#else
	#define _ALS_TextDrawSetPreviewRot
#endif
#define TextDrawSetPreviewRot(%0,%1,%2,%3,%4) DynamicTextDrawSetPreviewRot(%0, %1, %2, %3, %4, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_TextDrawSetPreviewVehicleColours
		#undef TextDrawSetPreviewVehicleColours
	#else
		#define _ALS_TextDrawSetPreviewVehicleColours
	#endif
	#define TextDrawSetPreviewVehicleColours(%0,%1,%2) DynamicTextDrawSetPreviewVehCol(%0, %1, %2, __file, __line)
#else
	#if defined _ALS_TextDrawSetPreviewVehCol
		#undef TextDrawSetPreviewVehCol
	#else
		#define _ALS_TextDrawSetPreviewVehCol
	#endif
	#define TextDrawSetPreviewVehCol(%0,%1,%2) DynamicTextDrawSetPreviewVehCol(%0, %1, %2, __file, __line)
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
#define PlayerTextDrawDestroy(%0,%1) DestroyDynamicPlayerTextDraw(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawLetterSize
	#undef PlayerTextDrawLetterSize
#else
	#define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize(%0,%1,%2,%3) DynamicPlayerTextDrawLetterSize(%0, %1, %2, %3, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawTextSize
	#undef PlayerTextDrawTextSize
#else
	#define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize(%0,%1,%2,%3) DynamicPlayerTextDrawTextSize(%0, %1, %2, %3, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawAlignment
	#undef PlayerTextDrawAlignment
#else
	#define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment(%0,%1,%2) DynamicPlayerTextDrawAlignment(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawColour
		#undef PlayerTextDrawColour
	#else
		#define _ALS_PlayerTextDrawColour
	#endif
	#define PlayerTextDrawColour(%0,%1,%2) DynamicPlayerTextDrawColour(%0, %1, %2, __file, __line)
#else
	#if defined _ALS_PlayerTextDrawColor
		#undef PlayerTextDrawColor
	#else
		#define _ALS_PlayerTextDrawColor
	#endif
	#define PlayerTextDrawColor(%0,%1,%2) DynamicPlayerTextDrawColour(%0, %1, %2, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawUseBox
	#undef PlayerTextDrawUseBox
#else
	#define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox(%0,%1,%2) DynamicPlayerTextDrawUseBox(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawBoxColour
		#undef PlayerTextDrawBoxColour
	#else
		#define _ALS_PlayerTextDrawBoxColour
	#endif
	#define PlayerTextDrawBoxColour(%0,%1,%2) DynamicPlayerTextDrawBoxColor(%0, %1, %2, __file, __line)
#else
	#if defined _ALS_PlayerTextDrawBoxColor
		#undef PlayerTextDrawBoxColor
	#else
		#define _ALS_PlayerTextDrawBoxColor
	#endif
	#define PlayerTextDrawBoxColor(%0,%1,%2) DynamicPlayerTextDrawBoxColor(%0, %1, %2, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetShadow
	#undef PlayerTextDrawSetShadow
#else
	#define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow(%0,%1,%2) DynamicPlayerTextDrawSetShadow(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetOutline
	#undef PlayerTextDrawSetOutline
#else
	#define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline(%0,%1,%2) DynamicPlayerTextDrawSetOutline(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawBackgroundColour
		#undef PlayerTextDrawBackgroundColour
	#else
		#define _ALS_PlayerTextDrawBackgroundColour
	#endif
	#define PlayerTextDrawBackgroundColour(%0,%1,%2) DynamicPlayerTextDrawBGColour(%0, %1, %2, __file, __line)
#else
	#if defined _ALS_PlayerTextDrawBackgroundCo
		#undef PlayerTextDrawBackgroundColor
	#else
		#define _ALS_PlayerTextDrawBackgroundCo
	#endif
	#define PlayerTextDrawBackgroundColor(%0,%1,%2) DynamicPlayerTextDrawBGColour(%0, %1, %2, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawFont
	#undef PlayerTextDrawFont
#else
	#define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont(%0,%1,%2) DynamicPlayerTextDrawFont(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawSetProportio
		#undef PlayerTextDrawSetProportional
	#else
		#define _ALS_PlayerTextDrawSetProportio
	#endif
	#define PlayerTextDrawSetProportional(%0,%1,%2) DynPlayerTextSetProportional(%0, %1, %2, __file, __line)
#else
	#if defined _ALS_PlayerTextDrawSetProportio
		#undef PlayerTextDrawSetProportional
	#else
		#define _ALS_PlayerTextDrawSetProportio
	#endif
	#define PlayerTextDrawSetProportional(%0,%1,%2) DynPlayerTextSetProportional(%0, %1, %2, __file, __line)
#endif
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetSelectabl
	#undef PlayerTextDrawSetSelectable
#else
	#define _ALS_PlayerTextDrawSetSelectabl
#endif
#define PlayerTextDrawSetSelectable(%0,%1,%2) DynamicPlayerTextDrawSelectable(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawShow
	#undef PlayerTextDrawShow
#else
	#define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow(%0,%1) DynamicPlayerTextDrawShow(%0, %1, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawHide
	#undef PlayerTextDrawHide
#else
	#define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide(%0,%1) DynamicPlayerTextDrawHide(%0, %1, __file, __line)
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
#define PlayerTextDrawSetPreviewModel(%0,%1,%2) DynamicPlayerTextDrawSetPrevMdl(%0, %1, %2, __file, __line)
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetPreviewRo
	#undef PlayerTextDrawSetPreviewRot
#else
	#define _ALS_PlayerTextDrawSetPreviewRo
#endif
#define PlayerTextDrawSetPreviewRot(%0,%1,%2,%3,%4,%5) DynamicPlayerTextDrawSetPrevRot(%0, %1, %2, %3, %4, %5, __file, __line)
/*******************************************************************************/
#if defined _INC_omp_textdraw
	#if defined _ALS_PlayerTextDrawSetPreviewVehicleColours
		#undef PlayerTextDrawSetPreviewVehicleColours
	#else
		#define _ALS_PlayerTextDrawSetPreviewVehicleColours
	#endif
	#define PlayerTextDrawSetPreviewVehicleColours(%0,%1,%2,%3) DynamicPlayerTextDrawPrevVehCol(%0, %1, %2, %3, __file, __line)
#else
	#if defined _ALS_PlayerTextDrawSetPreviewVe
		#undef PlayerTextDrawSetPreviewVehCol
	#else
		#define _ALS_PlayerTextDrawSetPreviewVe
	#endif
	#define PlayerTextDrawSetPreviewVehCol(%0,%1,%2,%3) DynamicPlayerTextDrawPrevVehCol(%0, %1, %2, %3, __file, __line)
#endif

/***
 *    888                            8888888888                                      888    
 *    888                            888                                             888    
 *    888                            888                                             888    
 *    888      .d88b.   .d88b.       8888888  .d88b.  888d888 88888b.d88b.   8888b.  888888 
 *    888     d88""88b d88P"88b      888     d88""88b 888P"   888 "888 "88b     "88b 888    
 *    888     888  888 888  888      888     888  888 888     888  888  888 .d888888 888    
 *    888     Y88..88P Y88b 888      888     Y88..88P 888     888  888  888 888  888 Y88b.  
 *    88888888 "Y88P"   "Y88888      888      "Y88P"  888     888  888  888 "Y888888  "Y888 
 *                          888                                                             
 *                     Y8b d88P                                                             
 *                      "Y88P"                                                              
 */

// Global
#define IsDynTextDrawVisibleForPlayer(%0,%1)				IsDynTextDrawVisibleForPlayer_(%0, %1, __file, __line)
#define DynamicTextDrawSetPos(%0,%1,%2)						DynamicTextDrawSetPos_(%0, %1, %2, __file, __line)
#define DynamicTextDrawGetLetterSize(%0,%1,%2)				DynamicTextDrawGetLetterSize_(%0, %1, %2, __file, __line)
#define DynamicTextDrawGetTextSize(%0,%1,%2)				DynamicTextDrawGetTextSize_(%0, %1, %2, __file, __line)
#define DynamicTextDrawGetPos(%0,%1,%2)						DynamicTextDrawGetPos_(%0, %1, %2, __file, __line)
#define DynamicTextDrawGetColour(%0)						DynamicTextDrawGetColour_(%0, __file, __line)
#define DynamicTextDrawGetBoxColour(%0)						DynamicTextDrawGetBoxColour_(%0, __file, __line)
#define DynamicTextDrawGetBackgroundCol(%0)					DynamicTextDrawGetBackgroundCo(%0, __file, __line)
#define DynamicTextDrawGetShadow(%0)						DynamicTextDrawGetShadow_(%0, __file, __line)
#define DynamicTextDrawGetOutline(%0)						DynamicTextDrawGetOutline_(%0, __file, __line)
#define DynamicTextDrawGetFont(%0)							DynamicTextDrawGetFont_(%0, __file, __line)
#define DynamicTextDrawIsBox(%0)							DynamicTextDrawIsBox_(%0, __file, __line)
#define DynamicTextDrawIsProportional(%0)					DynamicTextDrawIsProportional_(%0, __file, __line)
#define DynamicTextDrawIsSelectable(%0)						DynamicTextDrawIsSelectable_(%0, __file, __line)
#define DynamicTextDrawGetAlignment(%0)						DynamicTextDrawGetAlignment_(%0, __file, __line)
#define DynamicTextDrawGetPreviewModel(%0)					DynamicTextDrawGetPreviewModel_(%0, __file, __line)
#define DynamicTextDrawGetPreviewRot(%0,%1,%2,%3,%4)		DynamicTextDrawGetPreviewRot_(%0, %1, %2, %3, %4, __file, __line)
#define DynamicTextDrawGetPreviewVehCol(%0,%1,%2)			DynamicTextDrawGetPreviewVehCo(%0, %1, %2, __file, __line)
#define DynamicTextDrawGetRealID(%0,%1)						DynamicTextDrawGetRealID_(%0, %1, __file, __line)

// Player
#define IsDynamicPlayerTextDrawVisible(%0,%1)				IsDynamicPlayerTextDrawVisible_(%0, %1, __file, __line)
#define DynamicPlayerTextDrawSetPos(%0,%1,%2,%3)			DynamicPlayerTextDrawSetPos_(%0, %1, %2, %3, __file, __line)
#define DynPlayerTextDrawGetLetterSize(%0,%1,%2,%3)			DynPlayerTextDrawGetLetterSize_(%0, %1, %2, %3, __file, __line)
#define DynPlayerTextDrawGetTextSize(%0,%1,%2,%3)			DynPlayerTextDrawGetTextSize_(%0, %1, %2, %3, __file, __line)
#define DynamicPlayerTextDrawGetPos(%0,%1,%2,%3)			DynamicPlayerTextDrawGetPos_(%0, %1, %2, %3, __file, __line)
#define DynamicPlayerTextDrawGetColour(%0,%1)				DynamicPlayerTextDrawGetColour_(%0, %1, __file, __line)
#define DynamicPlayerTextDrawGetBoxCol(%0,%1)				DynamicPlayerTextDrawGetBoxCol_(%0, %1, __file, __line)
#define DynPlayerTextDrawGetBGColour(%0,%1)					DynPlayerTextDrawGetBGColour_(%0, %1, __file, __line)
#define DynamicPlayerTextDrawGetShadow(%0,%1)				DynamicPlayerTextDrawGetShadow_(%0, %1, __file, __line)
#define DynamicPlayerTextDrawGetOutline(%0,%1)				DynamicPlayerTextDrawGetOutlin_(%0, %1, __file, __line)
#define DynamicPlayerTextDrawGetFont(%0,%1)					DynamicPlayerTextDrawGetFont_(%0, %1, __file, __line)
#define DynamicPlayerTextDrawIsBox(%0,%1)					DynamicPlayerTextDrawIsBox_(%0, %1, __file, __line)
#define DynPlayerTextDrawIsProportional(%0,%1)				DynPlayerTextDrawIsProportiona_(%0, %1, __file, __line)
#define DynPlayerTextDrawIsSelectable(%0,%1)				DynPlayerTextDrawIsSelectable_(%0, %1, __file, __line)
#define DynPlayerTextDrawGetAlignment(%0,%1)				DynPlayerTextDrawGetAlignment_(%0, %1, __file, __line)
#define DynPlayerTextDrawGetPreviewMdl(%0,%1)				DynPlayerTextDrawGetPreviewMdl_(%0, %1, __file, __line)
#define DynPlayerTextDrawGetPreviewRot(%0,%1,%2,%3,%4,%5)	DynPlayerTextDrawGetPreviewRot_(%0, %1, %2, %3, %4, %5, __file, __line)
#define DynPlayerTextDrawGetPrevVehCol(%0,%1,%2,%3)			DynPlayerTextDrawGetPrevVehCol_(%0, %1, %2, %3, __file, __line)
#define PlayerTextDrawGetRealID(%0,%1,%2)					PlayerTextDrawGetRealID_(%0, %1, %2, __file, __line)