/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 960;

const Vector2 seats[ 3 ] = { Vector2( 0.0f, 500.0f ), Vector2( 180.0f, 500.0f ), Vector2( 360.0f, 500.0f ) };

void RenderStatic( SDL_Renderer* );
void DrawPause( SDL_Renderer* _renderer, TTF_Font* _font );
void DrawTitle( SDL_Renderer* _renderer, TTF_Font* _font );

int main( int argc, char* args[] )
{
	//srand( static_cast< unsigned int >( time( NULL ) ) );

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	else
	{
		if ( TTF_Init() < 0 )
		{
			std::cout << "TTF could not initialize! TTF_GetError: " << TTF_GetError() << std::endl;
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
	}

	TTF_Font * font = TTF_OpenFont( "calibrib.ttf", 20 );

	bool quit = false;
	SDL_Event e;

	float x = 0.0f;
	float y = 0.0f;
	float deltaTime = 0.033f;
	bool pause = false;

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
				if ( keyboardState[ SDL_SCANCODE_SPACE ] )
				{
					pause = !pause;
					if ( pause )
						deltaTime = 0.0f;
					else
						deltaTime = 0.033f;
				}
			}
		}

		SDL_SetRenderDrawColor( renderer, 0xAA, 0xAA, 0xAA, 0xFF );
		SDL_RenderClear( renderer );

		CrowdManager::GetInstance()->Update( deltaTime );
		CrowdManager::GetInstance()->Render( renderer );

		RenderStatic( renderer );

		if ( pause )
		{
			DrawPause( renderer, font );
		}
		else
		{
			DrawTitle( renderer, font );
		}

		SDL_RenderPresent( renderer );
	}

	TTF_CloseFont( font );	
	TTF_Quit();

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}

void RenderStatic( SDL_Renderer* _renderer )
{
	// bar
	{
		SDL_Rect fillRect = { 0, 640, 540, 90 };
		SDL_SetRenderDrawColor( _renderer, 0xCC, 0x66, 0x00, 0xFF );
		SDL_RenderFillRect( _renderer, &fillRect );

		SDL_Rect outlineRect = { 0, 640, 540, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( _renderer, &outlineRect );
	}

	// seats
	/*SDL_Rect seat1 = { ( int )seats[ 0 ].x, ( int )seats[ 0 ].y, 180, 90 };
	SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderDrawRect( _renderer, &seat1 );

	SDL_Rect seat2 = { ( int )seats[ 1 ].x, ( int )seats[ 1 ].y, 180, 90 };
	SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderDrawRect( _renderer, &seat2 );

	SDL_Rect seat3 = { ( int )seats[ 2 ].x, ( int )seats[ 2 ].y, 180, 90 };
	SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderDrawRect( _renderer, &seat3 );*/

	// options
	{
		SDL_Rect option1 = { 0, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( _renderer, &option1 );

		SDL_Rect option1out = { 0, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( _renderer, &option1out );


		SDL_Rect option2 = { 135, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0xFF, 0x00, 0xFF );
		SDL_RenderFillRect( _renderer, &option2 );

		SDL_Rect option2out = { 135, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( _renderer, &option2out );


		SDL_Rect option3 = { 270, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0xFF, 0xFF );
		SDL_RenderFillRect( _renderer, &option3 );

		SDL_Rect option3out = { 270, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( _renderer, &option3out );


		SDL_Rect option4 = { 405, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0xFF, 0x00, 0xFF, 0xFF );
		SDL_RenderFillRect( _renderer, &option4 );

		SDL_Rect option4out = { 405, 870, 135, 90 };
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( _renderer, &option4out );
	}
}

void DrawTitle( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, "Fiesta Baiona", color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { 200, 10, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void DrawPause( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( _renderer, &fillRect );

	SDL_Color color = { 255, 50, 50 };
	SDL_Surface * surfacePause = TTF_RenderText_Solid( _font, "- PAUSE -", color );
	SDL_Texture * texturePause = SDL_CreateTextureFromSurface( _renderer, surfacePause );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texturePause, NULL, NULL, &texW, &texH );
	SDL_Rect dstrectPause = { SCREEN_WIDTH / 2 - texW / 2, SCREEN_HEIGHT / 2 - texH / 2, texW, texH };
	SDL_RenderCopy( _renderer, texturePause, NULL, &dstrectPause );
	SDL_DestroyTexture( texturePause );
	SDL_FreeSurface( surfacePause );
}