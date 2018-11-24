/* GLM Studio @ copyright 2018 */

#pragma once

class Texture
{

};

class TextureManager
{
public:
	virtual void Init( Renderer* _renderer ) = 0;
	virtual Texture* LoadTexture( const char* _path ) const = 0;
	virtual void FreeTexture( Texture* _texture ) const = 0;
};