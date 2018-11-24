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
	_renderer->DrawText( 150, 150, 255, 0, 0, "Ongietorri chez toi grangue!", _fonter->Normal(), Font::CENTER );
	_renderer->DrawText( 150, 250, 255, 0, 0, "Clic left on the screen to start!", _fonter->Normal(), Font::CENTER );
}

void GameState_MainMenu::Exit()
{
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
	ActionsManager::GetInstance()->AddSelect( Vector2( 0.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option1" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 135.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option2" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 270.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option3" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 405.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option4" );

	ActionsManager::GetInstance()->AddServe( Vector2( 0.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar1", 0 );
	ActionsManager::GetInstance()->AddServe( Vector2( 180.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar2", 1 );
	ActionsManager::GetInstance()->AddServe( Vector2( 360.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar3", 2 );

	bgTexture = SDLTextureManager::GetInstance()->LoadTexture( "affiche.jpg" );
}

void GameState_Gameplay::Update( const float _dt, EventManager* _eventer )
{
	// UPDATE
	const int level = MoneyManager::GetInstance()->GetScore() / 100;

	ActionsManager::GetInstance()->Update( _dt, _eventer );
	CrowdManager::GetInstance()->Update( _dt * ( 1.0f + level * 0.1f ), _eventer );
}

void GameState_Gameplay::Render( Renderer* _renderer, FontManager* _fonter )
{
	ActionsManager::GetInstance()->Render( _renderer, _fonter );
	CrowdManager::GetInstance()->Render( _renderer, _fonter );
	MoneyManager::GetInstance()->Render( _renderer, _fonter );
	RenderStatic( _renderer );

	std::stringstream ossScore;
	ossScore << "Score: " << MoneyManager::GetInstance()->GetScore();
	_renderer->DrawText( 450, 50, 0, 0, 0, ossScore.str().c_str(), SDLFontManager::GetInstance()->Small() );

	const int level = MoneyManager::GetInstance()->GetScore() / 100;
	std::stringstream ossLevel;
	ossLevel << "Level: " << level + 1;
	_renderer->DrawText( 450, 65, 0, 0, 0, ossLevel.str().c_str(), SDLFontManager::GetInstance()->Small() );

	if ( parent->IsPaused() )
	{
		DrawPause( _renderer );
	}
	else
	{
		DrawTitle( _renderer );
	}

}

void GameState_Gameplay::Exit()
{
	SDLTextureManager::GetInstance()->FreeTexture( bgTexture );
}

void GameState_Gameplay::RenderStatic( Renderer* _renderer )
{
	_renderer->DrawFillRect( 0, 640, 540, 90, 0xCC, 0x66, 0x00, 0xFF );
	_renderer->DrawOutlineRect( 0, 640, 540, 90, 0x00, 0x00, 0x00, 0xFF );
}

void GameState_Gameplay::DrawTitle( Renderer* _renderer )
{
	_renderer->DrawText( 540 / 2, 20, 255, 0, 0, "Fiesta Baiona", SDLFontManager::GetInstance()->Normal(), Font::CENTER );
}

void GameState_Gameplay::DrawPause( Renderer* _renderer )
{
	_renderer->DrawBG( bgTexture, 0, 0 );
	_renderer->DrawFillRect( 0, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH, 20, 0xFF, 0xFF, 0xFF, 0xFF );
	_renderer->DrawText( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 50, 50, "- PAUSE -", SDLFontManager::GetInstance()->Normal(), Font::CENTER );
}