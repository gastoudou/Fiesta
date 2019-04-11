/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"

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