/* GLM Studio @ copyright 2018 */

#pragma once

#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

class SDLTexture : public Texture
{
public:
	SDL_Texture* texture;
};