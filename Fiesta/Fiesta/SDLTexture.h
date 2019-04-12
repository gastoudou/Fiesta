/* GLM Studio @ copyright 2018 */

#pragma once

#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

class SDLRenderer;

class SDLTexture : public Texture
{
	friend class SDLRenderer;

public:
	SDLTexture();
	virtual ~SDLTexture();

	const SDL_Texture* GetTexture() const;
	SDL_Texture* GetTexture();

	virtual int Width() const override;
	virtual int Height() const override;

private:
	SDL_Texture* texture = nullptr;
	int width = 0;
	int height = 0;
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
	bool m_init = false;
};