/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

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

	CrowdManager::GetInstance()->Add( Vector2( 2.0f, 2.0f ), Vector2( 0.0f, 1.0f ), 2.0f );

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
				if ( keyboardState[ SDL_SCANCODE_ESCAPE ] )
				{
					quit = true;
				}
			}
		}

		SDL_SetRenderDrawColor( renderer, 0xAA, 0xAA, 0xAA, 0xFF );
		SDL_RenderClear( renderer );

		CrowdManager::GetInstance()->Update( 0.033f );
		CrowdManager::GetInstance()->Render( renderer );

		SDL_RenderPresent( renderer );
	}

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}