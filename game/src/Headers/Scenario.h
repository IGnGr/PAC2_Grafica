#pragma once

#include "raylib.h"
#include <vector>


typedef enum ScenarioRectangleType { GROUND = 0, STAIRS = 1 } ScenarioRectangleType;


class ScenarioRectangle
{
private:
    ScenarioRectangleType m_type;
    Rectangle m_rectangle;
    Color m_color;

public:
    ScenarioRectangle();
    ScenarioRectangle(ScenarioRectangleType type, Rectangle rectangle);
    Rectangle GetRectangle();
    ScenarioRectangleType GetType() const;
    void Draw();
};

class Scenario
{
private:
    std::vector<ScenarioRectangle> m_scenarioRectangles;
    Texture2D m_backgroundSprite;

public:
    Scenario();
    Scenario(std::vector<ScenarioRectangle> scenarioRectangles, Texture2D backgroundSprite);
    void AddRectangle(ScenarioRectangle rect);
    void Draw(bool isHitboxVisible);

};

