#include "SoundManager.h"
#include "screens.h"

SoundManager::SoundManager()
{
	m_walkingSound = LoadSound("resources/Sound/SFX_Walking.mp3");
	m_jumpSound = LoadSound("resources/Sound/SFX_Jump.mp3");
	m_clearStageMusic = LoadMusicStream("resources/Sound/StageMusic_Clear.mp3");
}

void SoundManager::Update(float deltaTime)
{
	if (IsSoundPlaying(m_walkingSound) && m_walkingEnabled) PlayWalkingSound();
	UpdateMusicStream(m_clearStageMusic);
}

void SoundManager::PlayWalkingSound()
{
	m_walkingEnabled = true;

	PlaySound(m_walkingSound);
}

void SoundManager::StopWalkingSound()
{
	m_walkingEnabled = false;
}

void SoundManager::PlayJumpSound()
{
	PlaySound(m_jumpSound);
}

void SoundManager::PlayClearStageMusic()
{
	music = m_clearStageMusic;

}
