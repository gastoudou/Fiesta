/* GLM Studio @ copyright 2018 */

#pragma once

#include "Render.h"

#include <SDL.h>

const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 960;

class SDLRenderer : public Renderer
{
public:
	SDLRenderer();
	~SDLRenderer();

	virtual void Init();
	virtual void ShutDown();
	virtual void StartRender();
	virtual void EndRender();
	virtual void DrawFillRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const;
	virtual void DrawOutlineRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const;
	virtual void DrawText( int _x, int _y, int _r, int _g, int _b, const char* _text, Font* _font, Font::Format _format = Font::LEFT ) const;
	virtual void DrawBG( Texture* _texture, int _x, int _y );
	virtual void FreeTexture( Texture* _texture );
	virtual Texture* LoadTexture( const std::string& path );

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool init = false;
};