#pragma once
#include "stdafx.h"
#include <genesis.h>
#include "Render.h"
#include "SGDKTexture.h"

const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 960;

class SGDKRenderer : public Renderer
{
public:
	SGDKRenderer()
	{

	}

	virtual void Init()
	{
		SPR_init( 16, 256, 256 );
		init = true;
	}

	virtual void ShutDown()
	{
	}

	~SGDKRenderer() {}

	virtual void StartRender()
	{
	}

	virtual void EndRender()
	{
		SPR_update();
		VDP_waitVSync();
	}

	virtual void DrawFillRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const
	{
	}

	virtual void DrawOutlineRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const
	{
	}

	virtual void DrawText( int _x, int _y, int /*_r*/, int /*_g*/, int /*_b*/, const char* _text ) const
	{
		VDP_drawText( _text, _x, _y );
	}

	virtual void DrawBG( Texture* /*_texture*/, int /*_x*/, int /*_y*/ )
	{
	}

	virtual void FreeTexture( Texture* _texture )
	{
		delete _texture;
		_texture = NULL;
	}

	virtual Texture* LoadTexture( const std::string& path )
	{
		SGDKTexture* newTexture = new SGDKTexture;
		return newTexture;
	}

private:
	bool init = false;
};