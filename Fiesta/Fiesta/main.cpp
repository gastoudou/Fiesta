/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "CrowdManager.h"
#include "ActionsManager.h"
#include "MoneyManager.h"

#pragma optimize( "", off )

const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 960;

void RenderStatic( SDL_Renderer* );
void DrawPause( SDL_Renderer* _renderer, TTF_Font* _font );
void DrawTitle( SDL_Renderer* _renderer, TTF_Font* _font );
SDL_Texture* loadTexture( SDL_Renderer* _renderer, std::string path );

const float FIXED_TIME_STAMP = 0.066f;

int main( int argc, char* args[] )
{
	srand( static_cast< unsigned int >( time( NULL ) ) );

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
			window = SDL_CreateWindow( "Fiesta Baiona", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if ( window == NULL )
			{
				std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
				return -1;
			}
			else
			{
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_JPG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					return -1;
				}
			}
		}
	}

	TTF_Font * font = TTF_OpenFont( "calibrib.ttf", 20 );
	TTF_Font * small_font = TTF_OpenFont( "calibrib.ttf", 12 );

	bool quit = false;
	SDL_Event e;

	float x = 0.0f;
	float y = 0.0f;
	float deltaTime = FIXED_TIME_STAMP;
	bool pause = false;

	// add options
	ActionsManager::GetInstance()->AddSelect( Vector2( 0.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option1" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 135.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option2" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 270.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option3" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 405.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option4" );

	ActionsManager::GetInstance()->AddServe( Vector2( 0.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar1", 0 );
	ActionsManager::GetInstance()->AddServe( Vector2( 180.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar2", 1 );
	ActionsManager::GetInstance()->AddServe( Vector2( 360.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar3", 2 );


	// TEMP
	SDL_Texture* gTexture = loadTexture( renderer, "affiche.jpg" );

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
						deltaTime = FIXED_TIME_STAMP;
				}
			}
			ActionsManager::GetInstance()->HandleEvents( e );
		}

		SDL_SetRenderDrawColor( renderer, 0xBB, 0xBB, 0xBB, 0xFF );
		SDL_RenderClear( renderer );

		ActionsManager::GetInstance()->Update( deltaTime );
		CrowdManager::GetInstance()->Update( deltaTime );

		ActionsManager::GetInstance()->Render( renderer, small_font );
		CrowdManager::GetInstance()->Render( renderer, small_font );

		MoneyManager::GetInstance()->Render( renderer, small_font );
		RenderStatic( renderer );

		if ( pause )
		{
			SDL_RenderCopy( renderer, gTexture, NULL, NULL );
			DrawPause( renderer, font );
		}
		else
		{
			DrawTitle( renderer, font );
		}

		SDL_RenderPresent( renderer );
	}

	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	TTF_CloseFont( font );
	TTF_Quit();

	IMG_Quit();

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
}

void DrawTitle( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Color color = { 255, 0, 0 };
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
	SDL_Rect fillRect = { 0, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH, 20 };
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

SDL_Texture* loadTexture( SDL_Renderer* _renderer, std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}

#pragma optimize( "", on )