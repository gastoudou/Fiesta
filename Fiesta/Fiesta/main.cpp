/* GLM Studio @ copyright 2018 */

#include <iostream>
#include "vld.h"

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	else
	{
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if ( window == NULL )
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return -1;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		}
	}

	bool quit = false;
	SDL_Event e;

	float x = 0.0f;
	float y = 0.0f;

	while ( !quit )
	{
		while ( SDL_PollEvent( &e ) != 0 )
		{
			const Uint8* keyboardState = SDL_GetKeyboardState( NULL );

			if ( e.type == SDL_QUIT )
			{
				quit = true;
			}

			if ( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP )
			{
				if ( keyboardState[ SDL_SCANCODE_UP ] )
				{
					--y;
				}
				if ( keyboardState[ SDL_SCANCODE_DOWN ] )
				{
					++y;
				}
				if ( keyboardState[ SDL_SCANCODE_RIGHT ] )
				{
					++x;
				}
				if ( keyboardState[ SDL_SCANCODE_LEFT ] )
				{
					--x;
				}
			}
		}

		SDL_SetRenderDrawColor( renderer, 0xAA, 0xAA, 0xAA, 0xFF );
		SDL_RenderClear( renderer );

		SDL_Rect fillRect = { SCREEN_WIDTH / 4 + int(x), SCREEN_HEIGHT / 4 + int(y), 10, 10 };
		SDL_SetRenderDrawColor( renderer, 0xAA, 0x12, 0x34, 0xFF );
		SDL_RenderFillRect( renderer, &fillRect );

		SDL_RenderPresent( renderer );
	}

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}