#pragma once

#include "raylib.h"
#include <vector>
#include "Enemy.h"

typedef enum ScenarioRectangleType { GROUND = 0, STAIRS = 1 } ScenarioRectangleType;


class ScenarioRectangle
{
private:
    ScenarioRectangleType m_type;
    Rectangle m_rectangle;
    Color m_color;

public:
    ScenarioRectangle(void);
    ScenarioRectangle(ScenarioRectangleType type, Rectangle rectangle);
    Rectangle GetRectangle(void);
    ScenarioRectangleType GetType() const;
    void Draw(void);
};

class Scenario
{
private:
    std::vector<ScenarioRectangle> m_scenarioRectangles;
    std::vector<Enemy> m_scenarioEnemies;


    Texture2D m_backgroundSprite;

    float m_cakesTimeCounter;
    float m_barrelTimeCounter;
    float m_FireFlameCounter;


public:
    Scenario();
    Scenario(std::vector<ScenarioRectangle> scenarioRectangles, Texture2D backgroundSprite);
    void AddRectangle(ScenarioRectangle rect);
    void Draw(bool isHitboxVisible);
    void SpawnEnemies(float deltaTime);
    void Update(float deltaTime);
    std::vector<Enemy>* GetEnemies(void);
    std::vector<ScenarioRectangle>* GetScenarioRectangles(void);


};

