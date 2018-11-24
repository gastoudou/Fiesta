/* GLM Studio @ copyright 2018 */

#pragma once

#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

class SDLRenderer;

class SDLTexture : public Texture
{
public:
	SDL_Texture* texture;
};

class SDLTextureManager : public TextureManager
{
public:
	static SDLTextureManager* GetInstance()
	{
		static SDLTextureManager sInstance;
		return &sInstance;
	}

	virtual void Init( Renderer* _renderer );

	Texture*	LoadTexture( const char* _path ) const;
	void		FreeTexture( Texture* _texture ) const;

private:
	SDLRenderer* renderer = nullptr;
};