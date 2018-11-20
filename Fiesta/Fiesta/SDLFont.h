#pragma once

#include "Font.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class SDLFont : public Font
{
public:
	TTF_Font* font = NULL;
};

class SDLFontManager : public FontManager
{
public:

	static SDLFontManager* GetInstance()
	{
		static SDLFontManager s_instance;
		return &s_instance;
	}

	virtual void Init() override
	{
		if ( TTF_Init() < 0 )
		{
			std::cout << "TTF could not initialize! TTF_GetError: " << TTF_GetError() << std::endl;
			return;
		}

		font = new SDLFont;
		font->font = TTF_OpenFont( "calibrib.ttf", 20 );

		small_font = new SDLFont;
		small_font->font = TTF_OpenFont( "calibrib.ttf", 12 );

		init = true;
	}

	virtual void ShutDown() override
	{
		TTF_CloseFont( small_font->font );
		delete small_font;
		small_font = NULL;

		TTF_CloseFont( font->font );
		delete font;
		font = NULL;

		TTF_Quit();
	}

	virtual Font* Normal() const { return font; }
	virtual Font* Small() const { return small_font; }

private:

	SDLFont* font = NULL;
	SDLFont* small_font = NULL;

	bool init = false;
};