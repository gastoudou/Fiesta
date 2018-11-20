#pragma once

#include "Texture.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class SDLTexture : public Texture
{
public:
	SDL_Texture* texture;
};