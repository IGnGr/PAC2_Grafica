#include "Scenario.h"

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

}
