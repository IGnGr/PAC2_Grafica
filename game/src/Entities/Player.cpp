#include "Player.h"
#include <iostream>
#include <string>
#include "screens.h"

#define V_SPEED 600.0f
#define H_SPEED 300.0f
#define GRAVITY_SPEED 50.0f
#define STARTING_POSITION { 310.0f , 745.0f  }
#define STAIRS_SPEED 100.0f
#define STARTING_LIVES 3
#define SCORE_POSITION { 50.0f, 100.0f}
#define LIVES_POSITIONX 1000.0f
#define LIVES_POSITIONY 100.0f

#define LIVES_SPACING 50.0f


Player::Player(Scenario* scenario)
{
	m_position = STARTING_POSITION;
	m_direction = { 0,0 };
	m_speed = 0.0f;
	m_isGrounded = false;
	m_isInStairs = false;
	m_isJumping = false;
	m_isDead = false;
	m_hasWon = false;
	m_isDownstairs = false;
	m_hasDeathAnimationFinished = false;
	m_sprite = LoadTexture("resources/Characters/Mario_walk_right.png");
	nSpritesInFile = 3;
	m_points = 0;
	deathAnimationCount = 2;
	m_lives = STARTING_LIVES;
	m_scenario = scenario;
	m_scenarioRectangle = scenario->GetScenarioRectangles();
	m_scenarioEnemies = scenario->GetEnemies();
	m_width = m_sprite.width / nSpritesInFile;
	m_height = m_sprite.height;
	m_soundManager = new SoundManager();
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
	m_soundManager->PlayJumpSound();

}

void Player::MoveX(float deltaTime)
{
	if (m_isGrounded || m_isJumping)
	{
		m_position.x += m_direction.x * H_SPEED * deltaTime;

	}

	m_currentAnimationToPlay = m_direction.x > 0 && (m_isGrounded || m_isJumping )? m_horizontalRightMovementAnimation : m_currentAnimationToPlay;
	m_currentAnimationToPlay = m_direction.x < 0 && (m_isGrounded || m_isJumping) ? m_horizontalLeftMovementAnimation : m_currentAnimationToPlay;

	if (m_isGrounded)
	{
		m_soundManager->PlayWalkingSound();
	}

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
}


void Player::IsGrounded(float deltaTime)
{
	Rectangle playerHitBox = GetHitbox();

	for (auto &currentScenarioRectangle : *m_scenarioRectangle)
	{
		Rectangle rect = currentScenarioRectangle.GetRectangle();
		//if (CheckCollisionRecs(hitBox, rect.GetRectangle()) && rect.GetType() == ScenarioRectangleType::GROUND)

				
		if(rect.x <= playerHitBox.x + m_width / 2 &&
			rect.x + rect.width >= playerHitBox.x + m_width /2 &&
			rect.y - m_height >= playerHitBox.y &&
			rect.y - m_height <= playerHitBox.y + m_speed &&
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
	Rectangle newRect = { playerHitBox.x, playerHitBox.y + 1, playerHitBox.width,1};
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
			rect.x <= playerHitBox.x + m_width /2 &&
			rect.x + rect.width  >= playerHitBox.x + m_width/2 &&
			rect.y + rect.height - m_height >= playerHitBox.y  &&
			rect.y - m_height <= playerHitBox.y )

		{


			//Determines the correct animation for the climbing
			m_currentAnimationToPlay = m_isGrounded && m_isInStairs ? m_BeginEndClimbAnimation : m_verticalMovementAnimation;
			
			m_isInStairs = true;
			m_isDownstairs = isDownstairs({ rect.x,rect.y - m_height, rect.height , rect.height }, playerHitBox);
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

void Player::HandleEnemyCollisions(void)
{

	m_scenarioEnemies = m_scenario->GetEnemies();

	Rectangle playerHitBox = GetHitbox();

	for (auto& enemy : *m_scenarioEnemies)
	{
		if (CheckCollisionRecs(playerHitBox, enemy.GetHitbox()))
		{
			if (enemy.GetType() == EnemyType::KINGKONG)
				m_lives = 0;
			else
				m_lives--;


			m_scenario->clearAllEnemies();
			m_isDead = true;
			
		}


		Rectangle hitboxDown = { playerHitBox.x,playerHitBox.y + playerHitBox.height, playerHitBox.width, playerHitBox.height };
		if (CheckCollisionRecs( hitboxDown, enemy.GetHitbox()) && !enemy.HasBeenJumped() && m_isJumping)
		{
			m_points += 50;
			enemy.MarkJumped();
		}
	}

}

bool Player::GetIsGrounded()
{
	return m_isGrounded;
}

float Player::GetSpeed()
{
	return m_speed;
}

void Player::CheckIfPositionIsValid()
{
	if (m_position.y > GetScreenHeight())
	{
		m_position = STARTING_POSITION;
		m_lives--;
		m_isDead = true;
	}
}

void Player::HandleItemsCollisions(void)
{
	m_scenarioItems = m_scenario->GetScenarioItems();

	Rectangle playerHitBox = GetHitbox();

	for (auto& item : *m_scenarioItems)
	{
		if (CheckCollisionRecs(playerHitBox, item.GetHitbox()) && item.isEnabled())
		{
			if (item.GetType() == ItemType::PEACH)
			{
				m_hasWon = true;
				SaveStorageValue(0, 2);
				m_soundManager->PlayClearStageMusic();
			}
				
			if (item.GetType() == ItemType::BONUS1)
				m_points += 100;
			if (item.GetType() == ItemType::BONUS2)
				m_points += 200;
			if (item.GetType() == ItemType::BONUS3)
				m_points += 300;

			PlaySound(fxCoin);
			item.Disable();
		}
	}

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

		HandleEnemyCollisions();

		HandleItemsCollisions();

		CheckIfPositionIsValid();

		m_soundManager->Update(deltaTime);


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

		if (deathAnimationCount < -0.25)
		{
			m_hasDeathAnimationFinished = true;
			deathAnimationCount = 2;
			m_isDead = false;
		}
			
	}
	else
	{
		m_currentAnimationToPlay = m_deathAnimation;
	}

}


Rectangle Player::GetHitbox()
{
	return {  m_position.x - m_width /2 , m_position.y - m_height, m_width, m_height };
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



void Player::Draw()
{
	//DrawTexture(m_sprite, m_position.x - m_sprite.width / 2, m_position.y - m_sprite.height, WHITE);
	//DrawRectangle(GetHitbox().x, GetHitbox().y, GetHitbox().width, GetHitbox().height, ORANGE);

	//Rectangle source = { 0.0f, 0.0f, (float)m_sprite.width / nSpritesInFile, (float)m_sprite.height };
	//Rectangle dest = { m_position.x - source.width/ 2,m_position.y - source.height, source.width , source.height };

	//DrawTexturePro(m_sprite, source, dest,  { 0,0 }, 0, WHITE);


	//Score
	DrawTextEx(font, TextFormat("SCORE: %d", m_points), SCORE_POSITION, 40.0f, 2.0f, WHITE);

	//Lives
	DrawLives();

	m_currentAnimationToPlay->Draw();

}

void Player::DrawLives()
{
	for (int i = 0; i < m_lives; i++)
	{
		Rectangle source = { m_sprite.width / nSpritesInFile, 0.0f, (float)m_sprite.width / nSpritesInFile, (float)m_sprite.height };
		Rectangle dest = { LIVES_POSITIONX + i* LIVES_SPACING  ,LIVES_POSITIONY, source.width , source.height };


		DrawTexturePro(m_sprite, source, dest,  { 0,0 }, 0, WHITE);	}
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
	if (m_lives <= 0 && m_hasDeathAnimationFinished)
	{
		SaveStorageValue(0, 1);
		return true;

	}
	return false;
}
