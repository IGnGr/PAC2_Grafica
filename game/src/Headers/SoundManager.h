#pragma once

#include "raylib.h"

class SoundManager
{

private:
	Sound m_walkingSound;
	Sound m_jumpSound;
	Music m_clearStageMusic;

	bool m_walkingEnabled;


public:
	SoundManager();
	void Update(float deltaTime);
	void PlayWalkingSound();
	void StopWalkingSound();

	void PlayJumpSound();
	void PlayClearStageMusic();

};

