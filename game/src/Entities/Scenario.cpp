#include "Scenario.h"
#include <time.h>


#define LEFT_XLIMIT 290
#define RIGHT_XLIMIT 990

#define CAKES_MAX_SPAWN_TIME 4
#define CAKES_MIN_SPAWN_TIME 1
#define CAKES_SPEED 150.0f
#define CAKES_SPAWN_LOCATION {990,765}

#define BARREL_MIN_SPAWN_TIME 2
#define BARREL_MAX_SPAWN_TIME 6
#define FLAME_MIN_SPAWN_TIME 1
#define FLAME_MAX_SPAWN_TIME 5.5f


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

}

void Scenario::SpawnEnemies(float deltaTime)
{
    //Cakes
    m_cakesTimeCounter -= deltaTime;


    if (m_cakesTimeCounter <= 0.0f)
    {
        Enemy* newEnemy = new Enemy(CAKES_SPAWN_LOCATION, {-1,0}, CAKES_SPEED, EnemyType::CAKE );
        m_cakesTimeCounter = (rand() + CAKES_MIN_SPAWN_TIME) % CAKES_MAX_SPAWN_TIME;
        m_scenarioEnemies.push_back(*newEnemy);
    }

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
