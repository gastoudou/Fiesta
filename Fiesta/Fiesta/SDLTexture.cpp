/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"

void SDLTextureManager::Init( Renderer* _renderer )
{
	renderer = static_cast< SDLRenderer* >( _renderer );
}

Texture* SDLTextureManager::LoadTexture( const char* _path ) const
{
	return renderer->LoadTexture( _path );
}

void SDLTextureManager::FreeTexture( Texture* _texture ) const
{
	if ( _texture )
	{
		renderer->FreeTexture( _texture );
		_texture = nullptr;
	}
}