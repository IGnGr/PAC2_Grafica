#pragma once

#include "raylib.h"
#include "Animation.h"

typedef enum EnemyType { CAKE = 0, BARREL = 1, FIREBARREL = 2 , FLARE = 3, KINGKONG = 4 };


class Enemy
{

private:
	Vector2 m_position;
	Vector2 m_direction;
	float m_speed;
	Animation* m_currentAnimationToPlay;
	Rectangle m_hitBox;
	EnemyType m_enemyType;
	float m_width;
	float m_height;



public:

	Enemy(  Vector2 position, Vector2 direction, float speed , EnemyType enemyType);
	void MoveX(float deltaTime);
	Rectangle GetHitbox();
	Vector2 GetPosition();
	void Update(float deltaTime);
	void Draw();
	void SetAnimation();


};

