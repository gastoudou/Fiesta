/* GLM Studio @ copyright 2018 */

#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class SoundManager
{
public:
	~SoundManager();
	static SoundManager* GetInstance();

	void Init();
	void Update( const float );
	void ShutDown();

	int LoadSound( const std::string& _path );
	void PlaySound( const int _id );

private:
	SoundManager();
	SoundManager( const SoundManager& ) = delete;
	SoundManager& operator=( const SoundManager& ) = delete;

	Mix_Music* music = nullptr;
	std::vector< Mix_Chunk* > soundsFX;

	bool init = false;
};