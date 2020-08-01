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

#if defined _SCRIPT_UNLIMITED_TEXTDRAW_
	#endinput
#endif
#define _SCRIPT_UNLIMITED_TEXTDRAW_


// Definitions
#define	INVALID_DYNAMIC_TEXTDRAW (PlayerText: -1)

// Native
native PlayerText: CreatePTextdraw(playerid, Float: x, Float: y, const text[]);
native DestroyPTextdraw(playerid, PlayerText: text);
native PTextLetterSize(playerid, PlayerText: text, Float:x, Float:y);
native PTextSize(playerid, PlayerText: text, Float:x, Float:y);
native PTextAlignment(playerid, PlayerText: text, alignment);
native PTextColor(playerid, PlayerText: text, color);
native PTextUseBox(playerid, PlayerText: text, use);
native PTextBoxColor(playerid, PlayerText: text, color);
native PTextShadow(playerid, PlayerText: text, size);
native PTextOutline(playerid, PlayerText: text, size);
native PTextBGColor(playerid, PlayerText: text, color);
native PTextFont(playerid, PlayerText: text, font);
native PTextProportional(playerid, PlayerText: text, set);
native PTextSelectable(playerid, PlayerText: text, set);
native PTextShow(playerid, PlayerText: text);
native PTextHide(playerid, PlayerText: text);
native PTextSetString(playerid, PlayerText: text, const string[]);
native PTextPreviewModel(playerid, PlayerText: text, modelindex);
native PTextPreviewRot(playerid, PlayerText: text, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fZoom = 1.0);
native PTextPreviewVehCol(playerid, PlayerText: text, color1, color2);

// Callback
forward ClickDynamicPlayerTextdraw(playerid, PlayerText: playertextid);

// Modification
stock DYN_DestroyPTextdraw(playerid, &PlayerText: text)
{
	if(text != INVALID_DYNAMIC_TEXTDRAW)
	{
		DestroyPTextdraw(playerid, text);
		text = INVALID_DYNAMIC_TEXTDRAW;
	}
	return 1;
}

/*******************************************************************************/
#if defined _ALS_CreatePlayerTextDraw
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw CreatePTextdraw
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawDestroy
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy DYN_DestroyPTextdraw
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawLetterSize
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize PTextLetterSize
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawTextSize
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize PTextSize
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawAlignment
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment PTextAlignment
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawColor
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawColor
#endif
#define PlayerTextDrawColor PTextColor
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawUseBox
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox PTextUseBox
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawBoxColor
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawBoxColor
#endif
#define PlayerTextDrawBoxColor PTextBoxColor
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetShadow
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow PTextShadow
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetOutline
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline PTextOutline
/*******************************************************************************/
#if defined _ALS_PTextBgColor
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PTextBgColor
#endif
#define PlayerTextDrawBackgroundColor PTextBGColor
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawFont
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont PTextFont
/*******************************************************************************/
#if defined _ALS_PTextDrawSetProportional
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PTextDrawSetProportional
#endif
#define PlayerTextDrawSetProportional PTextProportional
/*******************************************************************************/
#if defined _ALS_PTextDrawSetSelectable
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PTextDrawSetSelectable
#endif
#define PlayerTextDrawSetSelectable PTextSelectable
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawShow
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow PTextShow
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawHide
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide PTextHide
/*******************************************************************************/
#if defined _ALS_PlayerTextDrawSetString
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString PTextSetString
/*******************************************************************************/
#if defined _ALS_PTextDrawSetPreviewModel
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PTextDrawSetPreviewModel
#endif
#define PlayerTextDrawSetPreviewModel PTextPreviewModel
/*******************************************************************************/
#if defined _ALS_PTextDrawSetPreviewRot
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PTextDrawSetPreviewRot
#endif
#define PlayerTextDrawSetPreviewRot PTextPreviewRot
/*******************************************************************************/
#if defined _ALS_PTextDrawSetPreviewVehCol
    #error Textdraw Streamer kutuphanesini ilk siralara yerlestirin.
#else
    #define _ALS_PTextDrawSetPreviewVehCol
#endif
#define PlayerTextDrawSetPreviewVehCol PTextPreviewVehCol
/*******************************************************************************/