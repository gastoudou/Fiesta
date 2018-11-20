/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "CrowdManager.h"
#include "ActionsManager.h"
#include "MoneyManager.h"

#include "SDLRenderer.h"
#include "SDLEvent.h"

#pragma optimize( "", off )

void RenderStatic( Renderer* );
void DrawPause( Renderer* _renderer );
void DrawTitle( Renderer* _renderer );

int main( int /*argc*/, char** /*args[]*/ )
{
	srand( static_cast< unsigned int >( time( NULL ) ) );

	bool quit = false;
	

	float deltaTime = EventManager::FIXED_TIME_STAMP;
	bool pause = false;

	// add options
	ActionsManager::GetInstance()->AddSelect( Vector2( 0.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option1" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 135.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option2" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 270.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option3" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 405.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option4" );

	ActionsManager::GetInstance()->AddServe( Vector2( 0.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar1", 0 );
	ActionsManager::GetInstance()->AddServe( Vector2( 180.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar2", 1 );
	ActionsManager::GetInstance()->AddServe( Vector2( 360.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar3", 2 );

	Renderer* renderer = new SDLRenderer;
	EventManager* eventer = new SDLEventManager;

	renderer->Init();

	// TEMP
	Texture* gTexture = renderer->LoadTexture( "affiche.jpg" );

	while ( !quit )
	{
		eventer->Update( quit, pause, deltaTime );

		// UPDATE
		ActionsManager::GetInstance()->Update( deltaTime );
		const int level = MoneyManager::GetInstance()->GetScore() / 100;
		CrowdManager::GetInstance()->Update( deltaTime * ( 1.0f + level * 0.1f ) );

		// RENDER
		renderer->StartRender();

		ActionsManager::GetInstance()->Render( renderer, SDLFontManager::GetInstance() );
		CrowdManager::GetInstance()->Render( renderer, SDLFontManager::GetInstance() );

		MoneyManager::GetInstance()->Render( renderer, SDLFontManager::GetInstance() );
		RenderStatic( renderer );

		std::stringstream oss;
		oss << "Level: " << level + 1;
		renderer->DrawText( 450, 50, 0, 0, 0, oss.str().c_str(), SDLFontManager::GetInstance()->Small() );

		if ( pause )
		{
			renderer->DrawBG( gTexture, 0, 0 );
			DrawPause( renderer );
		}
		else
		{
			DrawTitle( renderer );
		}

		renderer->EndRender();
	}

	renderer->FreeTexture( gTexture );
	renderer->ShutDown();

	return 0;
}

void RenderStatic( Renderer* _renderer )
{
	_renderer->DrawFillRect( 0, 640, 540, 90, 0xCC, 0x66, 0x00, 0xFF );
	_renderer->DrawOutlineRect( 0, 640, 540, 90, 0x00, 0x00, 0x00, 0xFF );
}

void DrawTitle( Renderer* _renderer )
{
	_renderer->DrawText( 540 / 2, 20, 255, 0, 0, "Fiesta Baiona", SDLFontManager::GetInstance()->Normal(), Font::CENTER );
}

void DrawPause( Renderer* _renderer )
{
	_renderer->DrawFillRect( 0, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH, 20, 0xFF, 0xFF, 0xFF, 0xFF );
	_renderer->DrawText( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 50, 50, "- PAUSE -", SDLFontManager::GetInstance()->Normal(), Font::CENTER );
}

#pragma optimize( "", on )