/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "MoneyManager.h"
#include <sstream>

void MoneyManager::Render( SDL_Renderer* _renderer, TTF_Font* _font ) const
{
	std::stringstream oss;
	oss << "Money: " << money;
	SDL_Color color = { 0, 0, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, oss.str().c_str(), color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { 350, 750, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void MoneyManager::AddMoney( int _money )
{
	money += _money;
}