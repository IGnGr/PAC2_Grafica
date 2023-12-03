#include "Enemy.h"


Enemy::Enemy(Vector2 position, Vector2 direction , float speed, EnemyType enemyType)
{
	m_position = position;
	m_direction = direction;
	m_speed = speed;
	m_enemyType = enemyType;

	SetAnimation();

	m_hitBox = { position.x - m_width /2 , position.y - m_height , m_width, m_height };


}

void Enemy::SetAnimation()
{
	Texture2D sprite;

	switch (m_enemyType)
	{
	case EnemyType::CAKE: 
		sprite = LoadTexture("resources/Enemies/Cake.png");
		m_currentAnimationToPlay = new Animation(sprite, 1, 1, m_position);
		m_width = sprite.width;
		m_height = sprite.height;

		break;
	case EnemyType::BARREL:
		sprite = LoadTexture("resources/Enemies/Barrel.png");
		m_currentAnimationToPlay = new Animation(sprite, 4, 10, m_position);
		m_width = sprite.width /4 ;
		m_height = sprite.height;

		break;
	case EnemyType::FIREBARREL:
		sprite = LoadTexture("resources/Enemies/BurningBarrel.png");
		m_currentAnimationToPlay = new Animation(sprite, 1, 1, m_position);
		m_width = sprite.width;
		m_height = sprite.height;

		break;
	case EnemyType::FLARE: 
		sprite = LoadTexture("resources/Enemies/FireFlame.png");
		m_currentAnimationToPlay = new Animation(sprite, 1, 1, m_position);
		m_width = sprite.width;
		m_height = sprite.height;

		break;
	case EnemyType::KINGKONG: 
		sprite = LoadTexture("resources/Enemies/DonkeyKong.png");
		m_currentAnimationToPlay = new Animation(sprite, 4, 10, m_position);
		m_width = sprite.width / 4;
		m_height = sprite.height;

		break;
	default: break;
	}


}

void Enemy::MoveX(float deltaTime)
{
	m_position.x += m_direction.x * m_speed * deltaTime;
}


Rectangle Enemy::GetHitbox()
{
	return m_hitBox;
}

Vector2 Enemy::GetPosition()
{
	return m_position;
}

void Enemy::Update(float deltaTime)
{
	MoveX(deltaTime);

	m_hitBox.x = m_position.x;
	m_hitBox.y = m_position.y;

	m_currentAnimationToPlay->Update(m_position);

}

void Enemy::Draw()
{
	DrawRectangle(GetHitbox().x, GetHitbox().y, GetHitbox().width, GetHitbox().height, PURPLE);
	m_currentAnimationToPlay->Draw();
}

