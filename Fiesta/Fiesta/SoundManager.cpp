/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() = default;

SoundManager::~SoundManager() = default;

SoundManager* SoundManager::GetInstance()
{
	static SoundManager s_instance;
	return &s_instance;
}


void SoundManager::Init()
{
	if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
	{
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return;
	}

	music = Mix_LoadMUS( "resources/hymne.mp3" );
	if ( music == nullptr )
	{
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return;
	}

	Mix_PlayMusic( music, -1 );
	Mix_VolumeMusic( 10 );

	init = true;
}

void SoundManager::Update( const float )
{
	if ( !init ) return;
}

int SoundManager::LoadSound( const std::string& _path )
{
	Mix_Chunk* newFX = Mix_LoadWAV( _path.c_str() );
	if ( newFX == nullptr )
	{
		std::cout << "Failed to load FX " << _path.c_str() << " SDL_mixer Error: " << Mix_GetError() << std::endl;
		return -1;
	}

	soundsFX.push_back( newFX );
	return ( int )soundsFX.size() - 1;
}

void SoundManager::PlaySound( const int _id )
{
	if ( _id >= 0 && _id < soundsFX.size() )
	{
		Mix_PlayChannel( -1, soundsFX[ _id ], 0 );
	}
}

void SoundManager::ShutDown()
{
	Mix_HaltMusic();

	for ( auto fx : soundsFX )
	{
		Mix_FreeChunk( fx );
		fx = nullptr;
	}
	soundsFX.clear();

	Mix_FreeMusic( music );
	music = nullptr;

	Mix_Quit();
}