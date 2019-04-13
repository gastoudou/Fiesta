/* GLM Studio @ copyright 2018 */

#pragma once

#include "Font.h"

class Texture;

class Renderer
{
public:
	Renderer(){}
	~Renderer() {}

	virtual void Init() = 0;
	virtual void ShutDown() = 0;

	virtual void DrawFillRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const = 0;
	virtual void DrawOutlineRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const = 0;
	virtual void DrawText( int _x, int _y, int _r, int _g, int _b, const char* _text, Font* _font, Font::Format _format = Font::LEFT ) const = 0;

	virtual void DrawBG( Texture* _texture, int _x, int _y, float _alpha ) = 0;
	virtual void DrawSprite( Texture* _texture, int _x, int _y, int _width, int _height, float _alpha ) = 0;

	virtual Texture* LoadTexture( const std::string& path ) = 0;
	virtual void FreeTexture( Texture* _texture ) = 0;

	virtual void StartRender() = 0;
	virtual void EndRender() = 0;
};