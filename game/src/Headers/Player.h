#pragma once

#include "raylib.h"
#include <vector>
#include "Scenario.h"
#include "Animation.h"

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
	bool m_isDead;
	bool m_hasWon;
	int nSpritesInFile;
	float deathAnimationCount;
	Texture2D m_sprite;
	Animation* m_currentAnimationToPlay;
	Animation* m_horizontalLeftMovementAnimation;
	Animation* m_horizontalRightMovementAnimation;
	Animation* m_verticalMovementAnimation;
	Animation* m_newFloorAnimation;
	Animation* m_BeginEndClimbAnimation;
	Animation* m_deathAnimation;
	Animation* m_deathEndAnimation;

	void PlayDeathAnimation();
	std::vector<ScenarioRectangle>* m_scenarioRectangle;
	void InitializeAnimations();


public:
	Player(std::vector<ScenarioRectangle>& scenarioRectangle);
	void Jump(float deltaTime);
	void MoveX(float deltaTime);
	void MoveY(float deltaTime);

	void IsGrounded(float deltaTime);
	void IsInStairs();
	Vector2 getSpriteCenter(const Texture2D& sprite);
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
	void Kill();
	bool hasWon();
	bool isDead();
};

