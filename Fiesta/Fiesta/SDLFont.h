/* GLM Studio @ copyright 2018 */

#pragma once

#include "Font.h"

#include <SDL_ttf.h>

class SDLFont : public Font
{
public:
	TTF_Font* font = NULL;
};

class SDLFontManager : public FontManager
{
public:
	static SDLFontManager* GetInstance();
	virtual void Init() override;
	virtual void ShutDown() override;
	virtual Font* Normal() const { return font; }
	virtual Font* Small() const { return small_font; }

private:
	SDLFont* font = NULL;
	SDLFont* small_font = NULL;

	bool init = false;
};