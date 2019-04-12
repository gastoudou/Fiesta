/* GLM Studio @ copyright 2018 */

#pragma once

class Texture
{
public:
	Texture() = default;
	virtual ~Texture() = default;

	virtual int Width() const = 0;
	virtual int Height() const = 0;

private:
	Texture( const Texture& ) = delete;
	Texture& operator=( const Texture& ) = delete;
};

class TextureManager
{
public:
	virtual void Init( Renderer* _renderer ) = 0;
	virtual Texture* LoadTexture( const char* _path ) const = 0;
	virtual void FreeTexture( Texture* _texture ) const = 0;
};