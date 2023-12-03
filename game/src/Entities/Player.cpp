#include "Player.h"
#include <iostream>

#define V_SPEED 600.0f
#define H_SPEED 300.0f
#define GRAVITY_SPEED 50.0f
#define STAIRS_SPEED 100.0f

Player::Player(std::vector<ScenarioRectangle>& scenarioRectangle)
{
	m_position = { 310.0f , 745.0f  };
	m_direction = { 0,0 };
	m_speed = 0.0f;
	m_isGrounded = false;
	m_isInStairs = false;
	m_isJumping = false;
	m_isDead = false;
	m_isDownstairs = false;
	m_sprite = LoadTexture("resources/Characters/Mario_walk_right.png");
	nSpritesInFile = 3;
	deathAnimationCount = 2;
	m_scenarioRectangle = &scenarioRectangle;

	InitializeAnimations();

	m_currentAnimationToPlay = m_horizontalRightMovementAnimation;
}


void Player::InitializeAnimations()
{
	Texture2D rightHorizontalMovementSprite = LoadTexture("resources/Characters/Mario_walk_right.png");
	m_horizontalRightMovementAnimation = new Animation(rightHorizontalMovementSprite, 3, 10, m_position);

	Texture2D leftHorizontalMovementSprite = LoadTexture("resources/Characters/Mario_walk_left.png");
	m_horizontalLeftMovementAnimation = new Animation(leftHorizontalMovementSprite, 3, 10, m_position);

	Texture2D verticalMovementSprite = LoadTexture("resources/Characters/Mario_Climb.png");
	m_verticalMovementAnimation = new Animation(verticalMovementSprite, 6, 10, m_position);

	Texture2D BeginEndClimbSprite = LoadTexture("resources/Characters/Mario_Idle_Climb.png");
	m_BeginEndClimbAnimation = new Animation(BeginEndClimbSprite, 1, 1, m_position);

	Texture2D deathSprite = LoadTexture("resources/Characters/Mario_Death.png");
	m_deathAnimation = new Animation(deathSprite, 4, 10, m_position);

	Texture2D endDeathSprite = LoadTexture("resources/Characters/Mario_Death_Idle.png");
	m_deathEndAnimation = new Animation(endDeathSprite, 1, 10, m_position);
}


void Player::Jump(float deltaTime)
{
	//m_position.y -= speed;
	m_speed = -V_SPEED* deltaTime;
	m_isJumping = true;
}

void Player::MoveX(float deltaTime)
{
	if (m_isGrounded || m_isJumping)
	{
		m_position.x += m_direction.x * H_SPEED * deltaTime;
	}

	m_currentAnimationToPlay = m_direction.x > 0 && (m_isGrounded || m_isJumping )? m_horizontalRightMovementAnimation : m_currentAnimationToPlay;
	m_currentAnimationToPlay = m_direction.x < 0 && (m_isGrounded || m_isJumping) ? m_horizontalLeftMovementAnimation : m_currentAnimationToPlay;

}

void Player::MoveY(float deltaTime)
{
	if (m_canJump) 	Jump(deltaTime);
	else if (m_isInStairs && !m_isJumping)
	{
		if (m_isDownstairs || m_direction.y > 0)
		{
			m_position.y -= m_direction.y * STAIRS_SPEED * deltaTime;
			m_speed = -m_direction.y * STAIRS_SPEED * deltaTime;
		}

	}
	else
	{
		m_position.y += m_speed;

	}




	std::cerr << "m_speed " << m_speed << std::endl;


}


void Player::IsGrounded(float deltaTime)
{
	Rectangle playerHitBox = GetHitbox();

	for (auto &currentScenarioRectangle : *m_scenarioRectangle)
	{
		Rectangle rect = currentScenarioRectangle.GetRectangle();
		//if (CheckCollisionRecs(hitBox, rect.GetRectangle()) && rect.GetType() == ScenarioRectangleType::GROUND)

				
		if(rect.x <= playerHitBox.x &&
			rect.x + rect.width >= playerHitBox.x &&
			rect.y  >= playerHitBox.y &&
			rect.y  <= playerHitBox.y + m_speed &&
			currentScenarioRectangle.GetType() == ScenarioRectangleType::GROUND)
		{
			m_isGrounded = true;
			m_isJumping = false;
			m_speed = 0;
			m_position.y = rect.y;
			return;
		}
	}
	m_isGrounded = false;
}

bool Player::isDownstairs(Rectangle StairsRectangle, Rectangle playerHitBox)
{
	Rectangle newRect = { playerHitBox.x, playerHitBox.y + 1, playerHitBox.width,playerHitBox.height };
	return CheckCollisionRecs(newRect, StairsRectangle);
}

void Player::IsInStairs()
{
	Rectangle playerHitBox = GetHitbox();
	float playerHitBoxArea = playerHitBox.height * playerHitBox.width;
	for (auto & currentScenarioRectangle : *m_scenarioRectangle)
	{

		Rectangle rect = currentScenarioRectangle.GetRectangle();

		//std::cerr << "CheckCollisionRecs(hitBox, rect.GetRectangle())" << (CheckCollisionRecs(hitBox, rect.GetRectangle())) << std::endl;

		//if (CheckCollisionRecs(hitBox, rect.GetRectangle()) && rect.GetType() == ScenarioRectangleType::STAIRS && m_direction.y != 0)
		if (currentScenarioRectangle.GetType() == ScenarioRectangleType::STAIRS && 
			rect.x <= playerHitBox.x &&
			rect.x + rect.width >= playerHitBox.x &&
			rect.y + rect.height >= playerHitBox.y  &&
			rect.y  <= playerHitBox.y )

		{


			//Determines the correct animation for the climbing
			m_currentAnimationToPlay = m_isGrounded && m_isInStairs ? m_BeginEndClimbAnimation : m_verticalMovementAnimation;
			
			m_isInStairs = true;
			m_isDownstairs = isDownstairs(rect, playerHitBox);
			return;

		}
	}

	m_isInStairs = false;
}

void Player::ApplyGravity(float deltaTime)
{

	//m_position.y += speed;

	if(!m_isInStairs || m_isInStairs && m_isJumping)
		m_speed += GRAVITY_SPEED * deltaTime;
	
}

Texture2D Player::GetSprite()
{
	return m_sprite;
}

Vector2 Player::GetPosition()
{
	return m_position;
}

bool Player::GetIsGrounded()
{
	return m_isGrounded;
}

float Player::GetSpeed()
{
	return m_speed;
}

void Player::Update(float deltaTime)
{
	if (!m_isDead) 
	{
		HandleInput();

		IsGrounded(deltaTime);

		IsInStairs();

		MoveX(deltaTime);

		MoveY(deltaTime);

		ApplyGravity(deltaTime);
	}
	else
	{
		PlayDeathAnimation();
	}

	m_currentAnimationToPlay->Update(m_position);
}

void Player::PlayDeathAnimation() 
{
	deathAnimationCount -= GetFrameTime();

	if (deathAnimationCount < 0)
	{
		m_currentAnimationToPlay = m_deathEndAnimation;
	}
	else
	{
		m_currentAnimationToPlay = m_deathAnimation;
	}

}


Rectangle Player::GetHitbox()
{
	return {  m_position.x , m_position.y, (float)m_sprite.width / 2* nSpritesInFile,(float)m_sprite.height };
}

void Player::HandleInput()
{
	m_direction = { 0,0 };

	//Horizontal component
	m_direction.x = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ? -1 : 0;
	m_direction.x = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ? 1 : m_direction.x;

	//Vertical component 
	m_direction.y = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ? 1 : 0;
	m_direction.y = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ? -1 : m_direction.y;

	//Jump
	m_canJump = IsKeyPressed(KEY_SPACE) && m_isGrounded;

}

 Vector2 Player::getSpriteCenter(const Texture2D& sprite)
{
	return { (float)sprite.width / 2 * nSpritesInFile, (float)sprite.height / 2};
}



void Player::Draw()
{
	//DrawTexture(m_sprite, m_position.x - m_sprite.width / 2, m_position.y - m_sprite.height, WHITE);
	//DrawRectangle(m_position.x - m_sprite.width / 2, m_position.y - m_sprite.height, m_sprite.width, m_sprite.height, ORANGE);

	//Rectangle source = { 0.0f, 0.0f, (float)m_sprite.width / nSpritesInFile, (float)m_sprite.height };
	//Rectangle dest = { m_position.x - source.width/ 2,m_position.y - source.height, source.width , source.height };

	//DrawTexturePro(m_sprite, source, dest,  { 0,0 }, 0, WHITE);
	m_currentAnimationToPlay->Draw();

}

void Player::Kill()
{
	m_isDead = true;
}

bool Player::hasWon()
{
	return m_hasWon;
}

bool Player::isDead()
{
	return m_isDead;
}
