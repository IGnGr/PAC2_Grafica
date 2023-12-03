/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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
#include "Player.h"
#include <iostream>
#include <time.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Music gameplayMusic;
Player* player;
Scenario* scenario;
std::vector<ScenarioRectangle> scenarioRectangles;

static int logoPositionX = 0;
static int logoPositionY = 0;
static Texture2D backgroundImage = { 0 };

bool ShowHitbox = true;


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------


void InitializeScenarioRectangles(void)
{

    //Initial platform
    ScenarioRectangle* platform1 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 290, 775 , 700, 25 });


    ScenarioRectangle* stairs1 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 370, 650 , 15, 125 });
    ScenarioRectangle* stairs2 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 545, 650 , 15, 125 });
    ScenarioRectangle* stairs3 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 720, 650 , 15, 125 });
    ScenarioRectangle* stairs4 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 895, 650 , 15, 125 });

    scenarioRectangles.push_back(*platform1);

    //1st floor
    ScenarioRectangle* platform2 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 315, 650 , 650, 25 });

    ScenarioRectangle* stairs5 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 495, 525 , 15, 125 });
    ScenarioRectangle* stairs6 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 745, 525 , 15, 125 });



    scenarioRectangles.push_back(*platform2);

    //2nd floor
    ScenarioRectangle* platform3 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 315, 525 , 125, 25 });
    ScenarioRectangle* platform4 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 490, 525 , 275, 25 });
    ScenarioRectangle* platform5 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 815, 525 , 150, 25 });


    ScenarioRectangle* stairs7 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 370, 400 , 15, 125 });
    ScenarioRectangle* stairs8 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 545, 400 , 15, 125 });
    ScenarioRectangle* stairs9 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 720, 400 , 15, 125 });
    ScenarioRectangle* stairs10 = new ScenarioRectangle(ScenarioRectangleType::STAIRS,{ 895, 400 , 15, 125 });

    scenarioRectangles.push_back(*platform3);
    scenarioRectangles.push_back(*platform4);
    scenarioRectangles.push_back(*platform5);


    //3rd floor
    ScenarioRectangle* platform6 = new ScenarioRectangle(ScenarioRectangleType::GROUND,{ 290, 400 , 300, 25 });
    ScenarioRectangle* platform7 = new ScenarioRectangle(ScenarioRectangleType::GROUND,{ 690, 400 , 300, 25 });


    ScenarioRectangle* stairs11 = new ScenarioRectangle(ScenarioRectangleType::STAIRS,{ 345, 275 , 15, 125 });
    ScenarioRectangle* stairs12 = new ScenarioRectangle(ScenarioRectangleType::STAIRS,{ 920, 275 , 15, 125 });


    scenarioRectangles.push_back(*platform6);
    scenarioRectangles.push_back(*platform7);

    //4th floor
    ScenarioRectangle* platform8 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 315, 275 , 650, 25 });

    scenarioRectangles.push_back(*platform8);

    ScenarioRectangle* stairs13 = new ScenarioRectangle(ScenarioRectangleType::STAIRS, { 695, 175 , 15, 100 });


    //Peach platform
    ScenarioRectangle* platform9 = new ScenarioRectangle(ScenarioRectangleType::GROUND, { 565, 175 , 150, 25 });

    scenarioRectangles.push_back(*platform9);



    scenarioRectangles.push_back(*stairs1);
    scenarioRectangles.push_back(*stairs2);
    scenarioRectangles.push_back(*stairs3);
    scenarioRectangles.push_back(*stairs4);
    scenarioRectangles.push_back(*stairs5);
    scenarioRectangles.push_back(*stairs6);
    scenarioRectangles.push_back(*stairs7);
    scenarioRectangles.push_back(*stairs8);
    scenarioRectangles.push_back(*stairs9);
    scenarioRectangles.push_back(*stairs10);
    scenarioRectangles.push_back(*stairs11);
    scenarioRectangles.push_back(*stairs12);
    scenarioRectangles.push_back(*stairs13);

}


void InitializeEnemies(void)
{

}


// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;


    StopMusicStream(music);
    gameplayMusic = LoadMusicStream("resources/Sound/StageMusic.mp3");
    PlayMusicStream(gameplayMusic);

    srand(time(NULL));

    backgroundImage = LoadTexture("resources/Maps/Custom_L2.png");



    InitializeScenarioRectangles();

    scenario = new Scenario(scenarioRectangles, backgroundImage);

    player = new Player(scenario);


    
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    UpdateMusicStream(gameplayMusic);

    // Press enter or tap to change to ENDING screen
    /*if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }*/

    float deltaTime = GetFrameTime();


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) ShowHitbox = !ShowHitbox;

    if (IsKeyPressed(KEY_K)) player->Kill();

    
    scenario->Update(deltaTime);
    player->Update(deltaTime);

    if (player->hasWon()) finishScreen = 1;
    if (player->isDead()) finishScreen = 1;

}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{


    scenario->Draw(ShowHitbox);

    //Drawing player
    player->Draw();

}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    UnloadMusicStream(gameplayMusic);

}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}