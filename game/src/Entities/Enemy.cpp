#include "Enemy.h"


Enemy::Enemy(Vector2 position, Vector2 direction , float speed, EnemyType enemyType)
{
	m_position = position;
	m_direction = direction;
	m_speed = speed;
	m_enemyType = enemyType;
	m_hasBeenJumped = false;
	SetAnimation();


}


void Enemy::SetAnimation()
{
	switch (m_enemyType){

	case EnemyType::CAKE: 
		m_sprite = LoadTexture("resources/Enemies/Cake.png");
		m_currentAnimationToPlay = new Animation(m_sprite, 1, 1, m_position);
		m_width = m_sprite.width;
		m_height = m_sprite.height;

		break;
	case EnemyType::BARREL:
		m_sprite = LoadTexture("resources/Enemies/Barrel.png");
		m_currentAnimationToPlay = new Animation(m_sprite, 4, 10, m_position);
		m_width = m_sprite.width /4 ;
		m_height = m_sprite.height;

		break;
	case EnemyType::FIREBARREL:
		m_sprite = LoadTexture("resources/Enemies/BurningBarrel.png");
		m_currentAnimationToPlay = new Animation(m_sprite, 1, 1, m_position);
		m_width = m_sprite.width;
		m_height = m_sprite.height;

		break;
	case EnemyType::FLARE: 
		m_sprite = LoadTexture("resources/Enemies/FireFlame.png");
		m_currentAnimationToPlay = new Animation(m_sprite, 1, 1, m_position);
		m_width = m_sprite.width;
		m_height = m_sprite.height;

		break;
	case EnemyType::KINGKONG: 
		m_sprite = LoadTexture("resources/Enemies/DonkeyKong.png");
		m_currentAnimationToPlay = new Animation(m_sprite, 4, 10, m_position);
		m_width = m_sprite.width / 4;
		m_height = m_sprite.height;

		break;
	default: break;
	}


}

EnemyType Enemy::GetType()
{
	return m_enemyType;
}

void Enemy::ReverseDirection()
{
	m_direction.x = -m_direction.x;
}

bool Enemy::HasBeenJumped(void)
{
	return m_hasBeenJumped;
}

void Enemy::MarkJumped(void)
{
	m_hasBeenJumped = true;
}

void Enemy::MoveX(float deltaTime)
{
	m_position.x += m_direction.x * m_speed * deltaTime;
}


Vector2 Enemy::GetPosition()
{
	return m_position;
}



Rectangle Enemy::GetHitbox()
{
	return { m_position.x - m_width / 2 , m_position.y - m_height, m_width, m_height };
}

void Enemy::Update(float deltaTime)
{
	MoveX(deltaTime);

	m_currentAnimationToPlay->Update(m_position);

}

void Enemy::Draw()
{
	//DrawRectangle(GetHitbox().x, GetHitbox().y, GetHitbox().width, GetHitbox().height, PURPLE);
	m_currentAnimationToPlay->Draw();
}

