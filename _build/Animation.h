#pragma once

#include "raylib.h"

class Animation
{
private:
	Texture2D m_sourceSprite;
	int m_currentIndex;
	int m_nTotalSprites;
	float m_animationTimer;
	int m_fpsRate;
	Vector2 m_position;

public:
	Animation();
	Animation(Texture2D sourceSprite, int currentIndex, int nTotalSprites, float animationTimer, int fpsRate, Vector2 position);
	void Draw();
	void SetPosition(Vector2 position);
	void Update();
	void SetInfo(Texture2D sourceSprite, int currentIndex, int nTotalSprites, float animationTimer, int fpsRate, Vector2 position);

};

