#pragma once

#include "raylib.h"
#include <vector>
#include "Scenario.h"
#include "Animation.h"
#include "Item.h"
#include "SoundManager.h"

class Player
{
private:
	Scenario* m_scenario;
	Vector2 m_position;
	Vector2 m_direction;
	int m_lives;
	int m_points;
	float m_speed;
	float m_width;
	float m_height;
	bool m_isGrounded;
	bool m_isInStairs;
	bool m_canJump;
	bool m_isJumping;
	bool m_isDownstairs;
	bool m_isDead;
	bool m_hasWon;
	bool m_hasDeathAnimationFinished;
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

	std::vector<ScenarioRectangle>* m_scenarioRectangle;
	std::vector<Enemy>* m_scenarioEnemies;
	std::vector<Item>* m_scenarioItems;

	SoundManager* m_soundManager;

	void InitializeAnimations();


public:
	Player(Scenario* scenario);
	void Jump(float deltaTime);
	void MoveX(float deltaTime);
	void MoveY(float deltaTime);

	void IsGrounded(float deltaTime);
	void IsInStairs(void);
	bool isDownstairs(Rectangle StairsRectangle, Rectangle playerHitBox);
	void ApplyGravity(float deltaTime);
	Texture2D GetSprite(void);
	Rectangle GetHitbox(void);
	Vector2 GetPosition(void);
	void HandleEnemyCollisions(void);
	bool GetIsGrounded(void);
	float GetSpeed(void);
	void Update(float deltaTime);
	void HandleInput(void);
	void Draw(void);
	void Kill(void);
	bool hasWon(void);
	bool isDead(void);
	void PlayDeathAnimation(void);
	void CheckIfPositionIsValid(void);
	void HandleItemsCollisions(void);
	void DrawLives(void);

};

