/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

#define OPTIONS_TEXT "Press 'O' to see how to play"
#define PLAY_TEXT "Press 'Enter' to play"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static int logoPositionX = 0;
static int logoPositionY = 0;
static int offsetBetweenMenuOptions = 100;
static int optionTextPositionY = 0;



static Texture2D backgroundImage = { 0 };


//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    backgroundImage = LoadTexture("resources/Menu/DonkeyKongMainLogo.png");

    logoPositionX = GetScreenWidth() / 2 - backgroundImage.width / 2;
    logoPositionY = GetScreenHeight() / 10 ;


    optionTextPositionY = 6 * logoPositionY;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 2;   // GAMEPLAY
        PlaySound(fxCoin);
    }

    if (IsKeyPressed(KEY_O))
    {
        finishScreen = 1;   // OPTIONS
        PlaySound(fxCoin);
    }

}

// Title Screen Draw logic
void DrawTitleScreen(void)
{

    //Filling the screen with the logo's color
    DrawTexturePro(backgroundImage, { 0,0,1,1 }, { 0,0, (float)GetScreenWidth(),(float)GetScreenHeight() }, { 0,0 }, 0, WHITE);
    DrawTexture(backgroundImage, logoPositionX, logoPositionY, WHITE);

    DrawTextEx(font, PLAY_TEXT, { (float)GetScreenWidth() / 2 - MeasureTextEx(font, PLAY_TEXT, TITLE_FONT_SIZE, STANDARD_TITLE_SPACING).x / 2,  (float)optionTextPositionY }, TITLE_FONT_SIZE, STANDARD_TITLE_SPACING, WHITE);
    DrawTextEx(font, OPTIONS_TEXT, { GetScreenWidth() / 2 - MeasureTextEx(font, OPTIONS_TEXT, TITLE_FONT_SIZE, STANDARD_TITLE_SPACING).x / 2,  (float)optionTextPositionY + offsetBetweenMenuOptions }, TITLE_FONT_SIZE, STANDARD_TITLE_SPACING, WHITE);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    UnloadTexture(backgroundImage);
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}