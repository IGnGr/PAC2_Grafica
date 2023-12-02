#pragma once

#include "raylib.h"
#include <vector>
#include "Scenario.h"

class Player
{
private:
	Vector2 m_position;
	Vector2 m_direction;
	float m_speed;
	bool m_isGrounded;
	bool m_isInStairs;
	bool m_canJump;
	bool m_isJumping;
	bool m_isDownstairs;
	Texture2D m_sprite;
	std::vector<ScenarioRectangle>* m_scenarioRectangle;

public:
	Player(std::vector<ScenarioRectangle>& scenarioRectangle);
	void Jump(float deltaTime);
	void MoveX(float deltaTime);
	void MoveY(float deltaTime);

	void IsGrounded(float deltaTime);
	void IsInStairs();

	bool isDownstairs(Rectangle StairsRectangle, Rectangle playerHitBox);
	void ApplyGravity(float deltaTime);
	Texture2D GetSprite();
	Rectangle GetHitbox();
	Vector2 GetPosition();
	bool GetIsGrounded();
	float GetSpeed();
	void Update(float deltaTime);
	void HandleInput();
	void Draw();

};

