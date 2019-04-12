/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "GameState.h"

#include "SDLFont.h"
#include "SDLRenderer.h"
#include "SDLEvent.h"
#include "SDLTexture.h"

#include "CrowdManager.h"
#include "ActionsManager.h"
#include "MoneyManager.h"

#include "GameStateManager.h"
#include "StateMachine.h"

GameState_MainMenu::GameState_MainMenu( GameStateManager* _parent )
	: parent( _parent )
{

}

GameState_MainMenu::~GameState_MainMenu()
{

}

void GameState_MainMenu::Enter()
{
	bgTexture = SDLTextureManager::GetInstance()->LoadTexture( "xavi.jpg" );
}

void GameState_MainMenu::Update( const float /*_dt*/, EventManager* _eventer )
{
	if ( _eventer->GetEvents().ClicLeft() )
	{
		parent->stateMachine->ChangeState( new GameState_Gameplay( parent ) );
	}
}

void GameState_MainMenu::Render( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawBG( bgTexture, 0, 0 );
	_renderer->DrawText( SCREEN_WIDTH / 2, 50, 255, 0, 255, "Ongietorri chez toi grangue!", _fonter->Normal(), Font::CENTER );
	_renderer->DrawText( SCREEN_WIDTH / 2, 100, 255, 0, 255, "Clic left on the screen to start!", _fonter->Small(), Font::CENTER );
}

void GameState_MainMenu::RenderDebug( Renderer*, FontManager* )
{

}

void GameState_MainMenu::Exit()
{
	SDLTextureManager::GetInstance()->FreeTexture( bgTexture );
}


GameState_Gameplay::GameState_Gameplay( GameStateManager* _parent )
	: parent( _parent )
{

}

GameState_Gameplay::~GameState_Gameplay()
{

}

void GameState_Gameplay::Enter()
{
	// add options
	const int interShelv = 540 / 5;
	ActionsManager::GetInstance()->AddSelect( Vector2( interShelv * 1, 870.0f ), "objRecipe1.png" );
	ActionsManager::GetInstance()->AddSelect( Vector2( interShelv * 2, 870.0f ), "objRecipe2.png" );
	ActionsManager::GetInstance()->AddSelect( Vector2( interShelv * 3, 870.0f ), "objRecipe3.png" );
	ActionsManager::GetInstance()->AddSelect( Vector2( interShelv * 4, 870.0f ), "objRecipe4.png" );

	ActionsManager::GetInstance()->AddServe( Vector2( CrowdManager::seatsInitialPosition[ 0 ].x, CrowdManager::seatsInitialPosition[ 0 ].y ), "objOrder1.png", 0 );
	ActionsManager::GetInstance()->AddServe( Vector2( CrowdManager::seatsInitialPosition[ 1 ].x, CrowdManager::seatsInitialPosition[ 1 ].y ), "objOrder2.png", 1 );
	ActionsManager::GetInstance()->AddServe( Vector2( CrowdManager::seatsInitialPosition[ 2 ].x, CrowdManager::seatsInitialPosition[ 2 ].y ), "objOrder3.png", 2 );

	if ( pauseTexture )
	{
		SDLTextureManager::GetInstance()->FreeTexture( pauseTexture );
		pauseTexture = nullptr;
	}

	bgFloorTexture = SDLTextureManager::GetInstance()->LoadTexture( "bgFloor.png" );
	bgWallsTexture = SDLTextureManager::GetInstance()->LoadTexture( "bgWalls.png" );
	barTexture = SDLTextureManager::GetInstance()->LoadTexture( "objBar.png" );
	shelfTexture = SDLTextureManager::GetInstance()->LoadTexture( "objShelf.png" );
	barmanTexture = SDLTextureManager::GetInstance()->LoadTexture( "spBarman.png" );

	pauseTexture = SDLTextureManager::GetInstance()->LoadTexture( "affiche.jpg" );
}

void GameState_Gameplay::Update( const float _dt, EventManager* _eventer )
{
	// UPDATE
	const int level = MoneyManager::GetInstance()->GetScore() / 100;

	//std::thread thread1( [ _dt, _eventer ]() {
		ActionsManager::GetInstance()->Update( _dt, _eventer );
	//} );

	//std::thread thread2( [ _dt, _eventer, level ]() {
		CrowdManager::GetInstance()->Update( _dt * ( 1.0f + level * 0.1f ), _eventer );
	//} );

	//thread1.join();
	//thread2.join();
}

void GameState_Gameplay::Render( Renderer* _renderer, FontManager* _fonter )
{
	if ( parent->IsPaused() )
	{
		DrawPause( _renderer );
	}
	else
	{
		RenderStatic( _renderer );

		ActionsManager::GetInstance()->Render( _renderer, _fonter );
		CrowdManager::GetInstance()->Render( _renderer, _fonter );
		MoneyManager::GetInstance()->Render( _renderer, _fonter );

		std::stringstream ossScore;
		ossScore << "Score: " << MoneyManager::GetInstance()->GetScore();
		_renderer->DrawText( 450, 50, 0, 0, 0, ossScore.str().c_str(), SDLFontManager::GetInstance()->Small() );

		const int level = MoneyManager::GetInstance()->GetScore() / 100;
		std::stringstream ossLevel;
		ossLevel << "Level: " << level + 1;
		_renderer->DrawText( 450, 65, 0, 0, 0, ossLevel.str().c_str(), SDLFontManager::GetInstance()->Small() );

		DrawTitle( _renderer );
	}
}

void GameState_Gameplay::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	ActionsManager::GetInstance()->RenderDebug( _renderer, _fonter );
	CrowdManager::GetInstance()->RenderDebug( _renderer, _fonter );
	MoneyManager::GetInstance()->RenderDebug( _renderer, _fonter );

	_renderer->DrawFillRect( ( int )CrowdManager::seatsInitialPosition[ 0 ].x, ( int )CrowdManager::seatsInitialPosition[ 0 ].y, 10, 10, 0, 0, 0, 255 );
	_renderer->DrawFillRect( ( int )CrowdManager::seatsInitialPosition[ 1 ].x, ( int )CrowdManager::seatsInitialPosition[ 1 ].y, 10, 10, 0, 0, 0, 255 );
	_renderer->DrawFillRect( ( int )CrowdManager::seatsInitialPosition[ 2 ].x, ( int )CrowdManager::seatsInitialPosition[ 2 ].y, 10, 10, 0, 0, 0, 255 );
}

void GameState_Gameplay::Exit()
{
	SDLTextureManager::GetInstance()->FreeTexture( pauseTexture );
	SDLTextureManager::GetInstance()->FreeTexture( bgWallsTexture );
	SDLTextureManager::GetInstance()->FreeTexture( bgFloorTexture );
	SDLTextureManager::GetInstance()->FreeTexture( barTexture );
	SDLTextureManager::GetInstance()->FreeTexture( shelfTexture );
	SDLTextureManager::GetInstance()->FreeTexture( barmanTexture );

	ActionsManager::GetInstance()->ShutDown();
	CrowdManager::GetInstance()->ShutDown();
	MoneyManager::GetInstance()->ShutDown();
}

void GameState_Gameplay::RenderStatic( Renderer* _renderer )
{
	_renderer->DrawBG( bgFloorTexture, 0, 0 );
	_renderer->DrawBG( bgWallsTexture, 0, 0 );

	_renderer->DrawSprite( barTexture, ( 540 - 464 ) / 2, 590, 464, barTexture->Height() );
	_renderer->DrawSprite( shelfTexture, ( 540 - 480 ) / 2, 860, 480, 40 );
	_renderer->DrawSprite( barmanTexture, 540 / 2 - 66 / 2, 590 + 98/2 + 86, 66, 86 );
}

void GameState_Gameplay::DrawTitle( Renderer* /*_renderer*/ )
{
	//_renderer->DrawText( 540 / 2, 20, 255, 0, 0, "Fiesta Baiona", SDLFontManager::GetInstance()->Normal(), Font::CENTER );
}

void GameState_Gameplay::DrawPause( Renderer* _renderer )
{
	_renderer->DrawBG( pauseTexture, 0, 0 );
	_renderer->DrawFillRect( 0, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH, 20, 0xFF, 0xFF, 0xFF, 0xFF );
	_renderer->DrawText( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 50, 50, "- PAUSE -", SDLFontManager::GetInstance()->Normal(), Font::CENTER );
}