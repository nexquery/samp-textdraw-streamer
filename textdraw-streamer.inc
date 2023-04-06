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

#if defined _INC_TEXTDRAW_STREAMER
	#endinput
#endif
#define _INC_TEXTDRAW_STREAMER

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
native PlayerText:CreatePTextDraw(playerid, Float:x, Float:y, const text[]);
native DestroyPTextdraw(playerid, PlayerText:text);
native PTextLetterSize(playerid, PlayerText:text, Float:x, Float:y);
native PTextSize(playerid, PlayerText:text, Float:x, Float:y);
native PTextAlignment(playerid, PlayerText:text, alignment);
native PTextColor(playerid, PlayerText:text, color);
native PTextUseBox(playerid, PlayerText:text, use);
native PTextBoxColor(playerid, PlayerText:text, color);
native PTextShadow(playerid, PlayerText:text, size);
native PTextOutline(playerid, PlayerText:text, size);
native PTextBGColor(playerid, PlayerText:text, color);
native PTextFont(playerid, PlayerText:text, font);
native PTextProportional(playerid, PlayerText:text, set);
native PTextSelectable(playerid, PlayerText:text, set);
native PTextShow(playerid, PlayerText:text);
native PTextHide(playerid, PlayerText:text);
native PTextSetString(playerid, PlayerText:text, const string[]);
native PTextPreviewModel(playerid, PlayerText:text, modelindex);
native PTextPreviewRot(playerid, PlayerText:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0);
native PTextPreviewVehCol(playerid, PlayerText:text, color1, color2);

// YSF Functions (names changed to avoid open.mp conflicts)
native IsValidPlayerTextDraw__(playerid, PlayerText:text);
native IsPlayerTextDrawVisible__(playerid, PlayerText:text);
native PlayerTextDrawGetString__(playerid, PlayerText:text, text_string[], len = sizeof(text_string));
native PlayerTextDrawSetPos__(playerid, PlayerText:text, Float:fX, Float:fY);
native PlayerTextDrawGetLetterSize__(playerid, PlayerText:text, &Float:fX, &Float:fY);
native PlayerTextDrawGetTextSize__(playerid, PlayerText:text, &Float:fX, &Float:fY);
native PlayerTextDrawGetPos__(playerid, PlayerText:text, &Float:fX, &Float:fY);
native PlayerTextDrawGetColor__(playerid, PlayerText:text);
native PlayerTextDrawGetBoxColor__(playerid, PlayerText:text);
native PlayerTextDrawGetBGColor__(playerid, PlayerText:text);
native PlayerTextDrawGetShadow__(playerid, PlayerText:text);
native PlayerTextDrawGetOutline__(playerid, PlayerText:text);
native PlayerTextDrawGetFont__(playerid, PlayerText:text);
native PlayerTextDrawIsBox__(playerid, PlayerText:text);
native PlayerTextDrawIsProportional__(playerid, PlayerText:text);
native PlayerTextDrawIsSelectable__(playerid, PlayerText:text);
native PlayerTextDrawGetAlignment__(playerid, PlayerText:text);
native PlayerTextDrawGetPreviewModel__(playerid, PlayerText:text);
native PlayerTextDrawGetPreviewRot__(playerid, PlayerText:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom);
native PlayerTextDrawGetPreviewVehCo__(playerid, PlayerText:text, &color1, &color2);

// Extra ID
native PlayerTextDrawSetExtraID(playerid, PlayerText:text, index, value);
native PlayerTextDrawGetExtraID(playerid, PlayerText:text, index);
native PlayerTextDrawResetExtraID(playerid, PlayerText:text);

// Array Data
native PlayerTextDrawSetArrayData(playerid, PlayerText:text, const src[], maxsrc = sizeof(src));
native PlayerTextDrawGetArrayData(playerid, PlayerText:text, dest[], maxdest = sizeof(dest));
native PlayerTextDrawRemoveArrayData(playerid, PlayerText:text);

// Get the real textdraw id generated
native PlayerTextDrawGetRealID(playerid, PlayerText:text);

// Total number of textdraws created for the player
native PlayerTextDrawSize(playerid);

/*******************************************************************************/
#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw CreatePTextdraw
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawDestroy
	#undef PlayerTextDrawDestroy
#else
	#define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy DestroyPTextdraw
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawLetterSize
	#undef PlayerTextDrawLetterSize
#else
	#define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize PTextLetterSize
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawTextSize
	#undef PlayerTextDrawTextSize
#else
	#define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize PTextSize
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawAlignment
	#undef PlayerTextDrawAlignment
#else
	#define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment PTextAlignment
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawColor
	#undef PlayerTextDrawColor
#else
	#define _ALS_PlayerTextDrawColor
#endif
#define PlayerTextDrawColor PTextColor
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawUseBox
	#undef PlayerTextDrawUseBox
#else
	#define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox PTextUseBox
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawBoxColor
	#undef PlayerTextDrawBoxColor
#else
	#define _ALS_PlayerTextDrawBoxColor
#endif
#define PlayerTextDrawBoxColor PTextBoxColor
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetShadow
	#undef PlayerTextDrawSetShadow
#else
	#define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow PTextShadow
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetOutline
	#undef PlayerTextDrawSetOutline
#else
	#define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline PTextOutline
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawBackgroundCo
	#undef PlayerTextDrawBackgroundColor
#else
	#define _ALS_PlayerTextDrawBackgroundCo
#endif
#define PlayerTextDrawBackgroundColor PTextBGColor
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawFont
	#undef PlayerTextDrawFont
#else
	#define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont PTextFont
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetProportio
	#undef PlayerTextDrawSetProportional
#else
	#define _ALS_PlayerTextDrawSetProportio
#endif
#define PlayerTextDrawSetProportional PTextProportional
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetSelectabl
	#undef PlayerTextDrawSetSelectable
#else
	#define _ALS_PlayerTextDrawSetSelectabl
#endif
#define PlayerTextDrawSetSelectable PTextSelectable
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawShow
	#undef PlayerTextDrawShow
#else
	#define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow PTextShow
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawHide
	#undef PlayerTextDrawHide
#else
	#define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide PTextHide
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString PTextSetString
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetPreviewMo
	#undef PlayerTextDrawSetPreviewModel
#else
	#define _ALS_PlayerTextDrawSetPreviewMo
#endif
#define PlayerTextDrawSetPreviewModel PTextPreviewModel
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetPreviewRo
	#undef PlayerTextDrawSetPreviewRot
#else
	#define _ALS_PlayerTextDrawSetPreviewRo
#endif
#define PlayerTextDrawSetPreviewRot PTextPreviewRot
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetPreviewVe
	#undef PlayerTextDrawSetPreviewVehCol
#else
	#define _ALS_PlayerTextDrawSetPreviewVe
#endif
#define PlayerTextDrawSetPreviewVehCol PTextPreviewVehCol
/*******************************************************************************/