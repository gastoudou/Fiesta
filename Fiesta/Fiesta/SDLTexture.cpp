/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"

SDLTexture::SDLTexture() = default;
SDLTexture::~SDLTexture() = default;

const SDL_Texture* SDLTexture::GetTexture() const
{
	return texture;
}

SDL_Texture* SDLTexture::GetTexture()
{
	return texture;
}

int SDLTexture::Width() const
{
	return width;
}

int SDLTexture::Height() const
{
	return height;
}

void SDLTextureManager::Init( Renderer* _renderer )
{
	renderer = static_cast< SDLRenderer* >( _renderer );
	m_init = true;
}

Texture* SDLTextureManager::LoadTexture( const char* _path ) const
{
	if ( !m_init )
		return nullptr;

	std::stringstream oss;
	oss << "resources/" << _path;
	return renderer->LoadTexture( oss.str().c_str() );
}

void SDLTextureManager::FreeTexture( Texture* _texture ) const
{
	if ( _texture )
	{
		renderer->FreeTexture( _texture );
		_texture = nullptr;
	}
}