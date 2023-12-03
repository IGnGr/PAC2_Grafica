#include "Animation.h"
#include "raylib.h"


Animation::Animation() {}

Animation::Animation(Texture2D sourceSprite, int nTotalSprites, int fpsRate, Vector2 position)
{
	m_sourceSprite = sourceSprite;
	m_nTotalSprites = nTotalSprites;
	m_animationTimer = 1.0 / fpsRate;
	m_fpsRate = fpsRate;
	m_position = position;
	m_currentIndex = 0;
}

void Animation::SetInfo(Texture2D sourceSprite, int nTotalSprites, int fpsRate, Vector2 position)
{
	m_sourceSprite = sourceSprite;
	m_nTotalSprites = nTotalSprites;
	m_animationTimer = 1.0 / fpsRate;
	m_fpsRate = fpsRate;
	m_position = position;
	m_currentIndex = 0;
}




void Animation::Draw()
{


	Rectangle source = { m_currentIndex * m_sourceSprite.width / m_nTotalSprites , 0.0f, (float)m_sourceSprite.width / m_nTotalSprites, (float)m_sourceSprite.height };
	Rectangle dest = { m_position.x - source.width / 2,m_position.y - source.height, source.width , source.height };

	DrawTexturePro(m_sourceSprite, source, dest, { 0,0 }, 0, WHITE);

}

void Animation::Update(Vector2 position)
{
	m_position = position;

	m_animationTimer -= GetFrameTime();
	if (m_animationTimer < 0)
	{
		m_animationTimer = 1.0 / m_fpsRate;
		m_currentIndex++;
		if (m_currentIndex >= m_nTotalSprites)
			m_currentIndex = 0;
	}
}

