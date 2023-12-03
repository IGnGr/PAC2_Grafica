/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
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

#define GOOD_ENDING_TEXT "CONGRATULATIONS, YOU'VE SAVED THE PRINCESS."
#define BAD_ENDING_TEXT "OH NO, YOU WERE UNABLE TO SAVE THE PRINCESS."
#define REST_OF_TEXT "PRESS 'O' TO GO TO THE OPTIONS OR 'ENTER' TO GO TO THE TITLE SCREEN"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
unsigned int ending = 0;
//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;


    // 1 = Death ; 2 = Win 
    ending = LoadStorageValue(0);

}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 2;   // TITLE
        PlaySound(fxCoin);
    }

    if (IsKeyPressed(KEY_O))
    {
        finishScreen = 1;   // OPTIONS
        PlaySound(fxCoin);
    }

}

static void DrawTextExCentered(Font font, const char* text, float fontSize, float spacing, Color tint, int offsetY)
{
    Vector2 position;
    position.x = GetScreenWidth() / 2 - MeasureTextEx(font, text, fontSize, spacing).x / 2;
    position.y = GetScreenHeight() / 2 - MeasureTextEx(font, text, fontSize, spacing).y / 2 + offsetY;
    DrawTextEx(font, text, position, fontSize, spacing, tint);
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    Vector2 pos = { 20, 10 };

    if(ending == 2)
        DrawTextExCentered(font, GOOD_ENDING_TEXT , TITLE_FONT_SIZE, STANDARD_TITLE_SPACING, WHITE, 0);
    else
        DrawTextExCentered(font, BAD_ENDING_TEXT, TITLE_FONT_SIZE, STANDARD_TITLE_SPACING, WHITE, 0);


    DrawTextExCentered(font, REST_OF_TEXT, TITLE_FONT_SIZE, STANDARD_TITLE_SPACING, WHITE, 50);

}
// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}