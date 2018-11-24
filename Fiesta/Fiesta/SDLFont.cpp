/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SDLFont.h"

SDLFontManager* SDLFontManager::GetInstance()
{
	static SDLFontManager s_instance;
	return &s_instance;
}

void SDLFontManager::Init()
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

void SDLFontManager::ShutDown()
{
	TTF_CloseFont( small_font->font );
	delete small_font;
	small_font = NULL;

	TTF_CloseFont( font->font );
	delete font;
	font = NULL;

	TTF_Quit();
}