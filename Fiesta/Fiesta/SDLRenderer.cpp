/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SDLRenderer.h"

#include "SDLTexture.h"
#include "SDLFont.h"


SDLRenderer::SDLRenderer()
{

}

SDLRenderer::~SDLRenderer()
{

}

void SDLRenderer::Init()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}
	else
	{
		SDLFontManager::GetInstance()->Init();

		window = SDL_CreateWindow( "Fiesta Baiona", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if ( window == NULL )
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			int intResult = IMG_Init( imgFlags );
			if ( ( intResult & imgFlags ) != imgFlags )
			{
				std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				return;
			}
		}
	}

	init = true;
}

void SDLRenderer::ShutDown()
{
	SDLFontManager::GetInstance()->ShutDown();
	IMG_Quit();

	SDL_DestroyWindow( window );
	SDL_Quit();
}

void SDLRenderer::StartRender()
{
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( renderer );
}

void SDLRenderer::EndRender()
{
	SDL_RenderPresent( renderer );
}

void SDLRenderer::DrawFillRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const
{
	SDL_Rect fillRect = { _x, _y, _width, _height };
	SDL_SetRenderDrawColor( renderer, ( Uint8 )_r, ( Uint8 )_g, ( Uint8 )_b, ( Uint8 )_a );
	SDL_RenderFillRect( renderer, &fillRect );
}

void SDLRenderer::DrawOutlineRect( int _x, int _y, int _width, int _height, int _r, int _g, int _b, int _a ) const
{
	SDL_Rect outlineRect = { _x, _y, _width, _height };
	SDL_SetRenderDrawColor( renderer, ( Uint8 )_r, ( Uint8 )_g, ( Uint8 )_b, ( Uint8 )_a );
	SDL_RenderDrawRect( renderer, &outlineRect );
}

void SDLRenderer::DrawText( int _x, int _y, int _r, int _g, int _b, const char* _text, Font* _font, Font::Format _format /*= Font::LEFT*/ ) const
{
	SDL_Color color = { ( Uint8 )_r, ( Uint8 )_g, ( Uint8 )_b };
	SDL_Surface * surface = TTF_RenderText_Solid( static_cast< SDLFont* >( _font )->font, _text, color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );

	int posX = _x;
	int posY = _y;

	if ( _format == Font::CENTER )
	{
		posX -= texW / 2;
		posY -= texH / 2;
	}
	SDL_Rect dstrect = { posX, posY, texW, texH };
	SDL_RenderCopy( renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void SDLRenderer::DrawBG( Texture* _texture, int /*_x*/, int /*_y*/, float _alpha )
{
	int ret = SDL_SetTextureAlphaMod( static_cast< SDLTexture* >( _texture )->GetTexture(), static_cast< Uint8 >( floorf( 255.0f * _alpha ) ) );
	if ( ret != 0 )
	{
		std::cout << "SDL_SetTextureAlphaMod error: " << SDL_GetError() << std::endl;
	}

	ret = SDL_RenderCopy( renderer, static_cast< SDLTexture* >( _texture )->GetTexture(), NULL, NULL );
	if ( ret != 0 )
	{
		std::cout << "SDL_SetTextureAlphaMod error: " << SDL_GetError() << std::endl;
	}
}

void SDLRenderer::DrawSprite( Texture* _texture, int _x, int _y, int _width, int _height, float _alpha )
{
	int ret = SDL_SetTextureAlphaMod( static_cast< SDLTexture* >( _texture )->GetTexture(), static_cast< Uint8 >( floorf( 255.0f * _alpha ) ) );
	if ( ret != 0 )
	{
		std::cout << "SDL_SetTextureAlphaMod error: " << SDL_GetError() << std::endl;
	}

	SDL_Rect dest = { _x, _y, _width, _height };
	ret = SDL_RenderCopy( renderer, static_cast< SDLTexture* >( _texture )->GetTexture(), NULL, &dest );
	if ( ret != 0 )
	{
		std::cout << "SDL_SetTextureAlphaMod error: " << SDL_GetError() << std::endl;
	}
}

void SDLRenderer::FreeTexture( Texture* _texture )
{
	SDL_DestroyTexture( static_cast< SDLTexture* >( _texture )->GetTexture() );
	delete _texture;
	_texture = NULL;
}

Texture* SDLRenderer::LoadTexture( const std::string& _path )
{
	SDLTexture* newTexture = new SDLTexture;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( _path.c_str() );

	if ( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", _path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		newTexture->texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture->texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", _path.c_str(), SDL_GetError() );
		}

		int ret = SDL_QueryTexture( newTexture->texture, NULL, NULL, &newTexture->width, &newTexture->height );
		assert( ret == 0 );
		if ( ret < 0 )
			std::cout << "SDL could not query texture. SDL_Error: " << SDL_GetError();

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}