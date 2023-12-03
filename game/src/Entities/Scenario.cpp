#include "Scenario.h"
#include <time.h>


#define LEFT_XLIMIT 350
#define RIGHT_XLIMIT 925

#define CAKES_MAX_SPAWN_TIME 4
#define CAKES_MIN_SPAWN_TIME 1
#define CAKES_SPEED 150.0f
#define CAKES_SPAWN_LOCATION {925,775}
#define CAKES_DIRECTION {-1,0}

#define BARREL_MIN_SPAWN_TIME 2
#define BARREL_MAX_SPAWN_TIME 6
#define BARREL_SPEED 150.0f
#define BARREL_SPAWN_LOCATION {350,650}
#define BARREL_DIRECTION {1,0}

#define FLAME_MIN_SPAWN_TIME 1
#define FLAME_MAX_SPAWN_TIME 5.5f
#define FLAME_SPEED 150.0f
#define FLAME_SPAWN_LOCATION1 {590,400}
#define FLAME_SPAWN_LOCATION2 {685,400}

#define BARRELFLARE_LOCATION {640,450}
#define KINGKONG_LOCATION {375,275}
#define KINGKONG_SPEED 150.0f

#define BONUS1_LOCATION {930,520}
#define BONUS2_LOCATION {640,520}
#define BONUS3_LOCATION {330,520}
#define PEACH_LOCATION {580,170}



ScenarioRectangle::ScenarioRectangle()
{
}

ScenarioRectangle::ScenarioRectangle(ScenarioRectangleType type, Rectangle rectangle)
{
    m_type = type;
    m_rectangle = rectangle;    
}


Rectangle ScenarioRectangle::GetRectangle()
{
    return m_rectangle;
}

ScenarioRectangleType ScenarioRectangle::GetType() const
{
    return m_type;
}

void ScenarioRectangle::Draw()
{
    Color color = { 0,0,0,0 };

    if (m_type == ScenarioRectangleType::GROUND) color = RED;
    if (m_type == ScenarioRectangleType::STAIRS) color = BLUE;

    DrawRectangle(m_rectangle.x, m_rectangle.y, m_rectangle.width, m_rectangle.height, color);

}
    

Scenario::Scenario(std::vector<ScenarioRectangle> scenarioRectangles, Texture2D backgroundSprite)
{
    m_scenarioRectangles = scenarioRectangles;
    m_backgroundSprite = backgroundSprite;
    m_cakesTimeCounter = 0;
    m_barrelTimeCounter = 0;
    m_FireFlameCounter = 0;


    SpawnPermanentEnemies();
    SpawnItems();

}


void Scenario::AddRectangle(ScenarioRectangle rect)
{
    m_scenarioRectangles.push_back(rect);
}


void Scenario::Draw(bool isHitboxVisible)
{

    //Filling the screen with the background's color
    DrawTexturePro(m_backgroundSprite, { 0,0,1,1 }, { 0,0, (float)GetScreenWidth(),(float)GetScreenHeight() }, { 0,0 }, 0, WHITE);

    float backgroundPositionX = GetScreenWidth() / 2 - m_backgroundSprite.width / 2;
    float backgroundPositionY = GetScreenHeight() / 2 - m_backgroundSprite.height / 2;

    //Using the background image 
    DrawTexture(m_backgroundSprite, backgroundPositionX, backgroundPositionY, WHITE);

    if (isHitboxVisible)
    {
        //Drawing all the rectangles for the scenario hit boxes
        for (auto& currentRectangle : m_scenarioRectangles)
        {
            currentRectangle.Draw();
        }
    }


    for (auto enemy : m_scenarioEnemies)
    {
        enemy.Draw();
    }

    for (auto item : m_scenarioItems)
    {
        item.Draw();
    }

}

void Scenario::SpawnPermanentEnemies()
{
    //FlameBarrel
    Enemy* newEnemy = new Enemy(BARRELFLARE_LOCATION, {0,0}, 0, EnemyType::FIREBARREL);
    m_scenarioEnemies.push_back(*newEnemy);

    //King kong
    newEnemy = new Enemy(KINGKONG_LOCATION, { 1,0 }, KINGKONG_SPEED, EnemyType::KINGKONG);
    m_scenarioEnemies.push_back(*newEnemy);

}


void Scenario::SpawnEnemies(float deltaTime)
{
    //Cakes
    m_cakesTimeCounter -= deltaTime;


    if (m_cakesTimeCounter <= 0.0f)
    {
        Enemy* newEnemy = new Enemy(CAKES_SPAWN_LOCATION, CAKES_DIRECTION, CAKES_SPEED, EnemyType::CAKE );
        m_cakesTimeCounter = (rand() + CAKES_MIN_SPAWN_TIME) % CAKES_MAX_SPAWN_TIME;
        m_scenarioEnemies.push_back(*newEnemy);
    }

    //Barrels
    m_barrelTimeCounter -= deltaTime;


    if (m_barrelTimeCounter <= 0.0f)
    {
        Enemy* newEnemy = new Enemy(BARREL_SPAWN_LOCATION, BARREL_DIRECTION, BARREL_SPEED, EnemyType::BARREL);
        m_barrelTimeCounter = (rand() + BARREL_MIN_SPAWN_TIME) % BARREL_MAX_SPAWN_TIME;
        m_scenarioEnemies.push_back(*newEnemy);
    }




    //Flames
    m_FireFlameCounter -= deltaTime;


    if (m_FireFlameCounter <= 0.0f)
    {
        bool leftFlame = (rand()) % 2 == 1;

        Vector2 location;


        if (leftFlame) location = FLAME_SPAWN_LOCATION1;
        else location = FLAME_SPAWN_LOCATION2;

        Vector2 direction;

        if (leftFlame) direction = { -1,0 };
        else direction = { 1,0 };

        Enemy* newEnemy = new Enemy(location, direction, FLAME_SPEED, EnemyType::FLARE);
        m_FireFlameCounter = FLAME_MIN_SPAWN_TIME + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (FLAME_MAX_SPAWN_TIME - FLAME_MIN_SPAWN_TIME)));
        m_scenarioEnemies.push_back(*newEnemy);
    }

}

void Scenario::SpawnItems(void)
{
    Item* item;


    //Bonus1
    Texture2D bonus1Sprite = LoadTexture("resources/Bonus/Bonus1.png");
    item = new Item(BONUS1_LOCATION, bonus1Sprite,ItemType::BONUS1);
    m_scenarioItems.push_back(*item);

    //Bonus2
    Texture2D bonus2Sprite = LoadTexture("resources/Bonus/Bonus2.png");
    item = new Item(BONUS2_LOCATION, bonus2Sprite, ItemType::BONUS2);
    m_scenarioItems.push_back(*item);


    //Bonus3
    Texture2D bonus3Sprite = LoadTexture("resources/Bonus/Bonus3.png");
    item = new Item(BONUS3_LOCATION, bonus3Sprite, ItemType::BONUS3);
    m_scenarioItems.push_back(*item);


    //Peach
    Texture2D peachSprite = LoadTexture("resources/Characters/Peach.png");
    item = new Item(PEACH_LOCATION, peachSprite, ItemType::PEACH);
    m_scenarioItems.push_back(*item);


}

void Scenario::Update(float deltaTime)
{
    SpawnEnemies(deltaTime);

    std::vector<Enemy> newEnemyVector;


    for (auto &enemy : m_scenarioEnemies)
    {
        enemy.Update(deltaTime);

        if (enemy.GetPosition().x >= LEFT_XLIMIT && enemy.GetPosition().x <= RIGHT_XLIMIT)
        {

            newEnemyVector.push_back(enemy);
        }
        else
        {
            if (enemy.GetType() == EnemyType::KINGKONG)
            {
                enemy.ReverseDirection();
                newEnemyVector.push_back(enemy);

            }
        }
    }

    m_scenarioEnemies = newEnemyVector;

}

std::vector<Enemy>* Scenario::GetEnemies(void)
{
    return &m_scenarioEnemies;
}

std::vector<ScenarioRectangle>* Scenario::GetScenarioRectangles(void)
{
    return &m_scenarioRectangles;
}

std::vector<Item>* Scenario::GetScenarioItems(void)
{
    return &m_scenarioItems;
}

void Scenario::clearAllEnemies(void)
{
    m_scenarioEnemies.clear();
    SpawnPermanentEnemies();
}
