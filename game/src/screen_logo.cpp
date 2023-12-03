/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Logo Screen Functions Definitions (Init, Update, Draw, Unload)
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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

static int logoPositionX = 0;
static int logoPositionY = 0;

static Texture2D backgroundImage = { 0 };


//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void)
{
    finishScreen = 0;


    backgroundImage = LoadTexture("resources/uoc.png");


    logoPositionX = GetScreenWidth() / 2 - backgroundImage.width / 2;
    logoPositionY = GetScreenHeight() / 2 - backgroundImage.height / 2;


}

// Logo Screen Update logic
void UpdateLogoScreen(void)
{

    framesCounter++;

    if (framesCounter > 200)
    {
        finishScreen = 1;   // Jump to next screen
    }
  
}

// Logo Screen Draw logic
void DrawLogoScreen(void)
{
    //Filling the screen with the logo's color
    DrawTexturePro(backgroundImage, { 0,0,1,1 }, { 0,0, (float)GetScreenWidth(),(float)GetScreenHeight() }, { 0,0 }, 0, WHITE);

    //Using the image
    DrawTexture(backgroundImage, logoPositionX, logoPositionY, WHITE);
}

// Logo Screen Unload logic
void UnloadLogoScreen(void)
{
    UnloadTexture(backgroundImage);
}

// Logo Screen should finish?
int FinishLogoScreen(void)
{
    return finishScreen;
}
