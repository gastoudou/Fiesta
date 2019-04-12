/* GLM Studio @ copyright 2018 */

#pragma once

#include "Render.h"

#include <SDL.h>
#include <SDL_render.h>

const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 960;

class SDLRenderer : public Renderer
{
public:
	SDLRenderer();
	~SDLRenderer();

	virtual void Init() override;
	virtual void ShutDown() override;
	virtual void StartRender() override;
	virtual void EndRender() override;
	virtual void DrawFillRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const override;
	virtual void DrawOutlineRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const override;
	virtual void DrawText( int _x, int _y, int _r, int _g, int _b, const char* _text, Font* _font, Font::Format _format = Font::LEFT ) const override;
	
	virtual void DrawBG( Texture* _texture, int _x, int _y ) override;
	virtual void DrawSprite( Texture* _texture, int _x, int _y, int _width, int _height ) override;

	virtual void FreeTexture( Texture* _texture ) override;
	virtual Texture* LoadTexture( const std::string& path ) override;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool init = false;
};