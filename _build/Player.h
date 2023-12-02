#pragma once

#include "raylib.h"
#include <vector>
#include "ScenarioRectangle.h"

class Player
{
private:
	Vector2 m_position;
	float m_speed;
	bool m_isGrounded;
	Texture2D m_sprite;

public:
	Player();
	void Jump(float speed);
	void Move(Vector2 direction, float speed);
	void IsGrounded(std::vector<ScenarioRectangle> scenarioRectangle);
	void ApplyGravity(float speed);
	Texture2D GetSprite();
	Vector2 GetPosition();
	bool GetIsGrounded();
	float GetSpeed();
	
};

