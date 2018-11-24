/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "GameStateManager.h"

#include "SDLFont.h"
#include "SDLRenderer.h"
#include "SDLEvent.h"

#include "StateMachine.h"
#include "GameState.h"

GameStateManager::GameStateManager()
{
	srand( static_cast< unsigned int >( time( NULL ) ) );

	stateMachine = new StateMachine;
	stateMachine->ChangeState( new GameState_MainMenu( this ) );

	quit = false;
	deltaTime = EventManager::FIXED_TIME_STAMP;

	renderer = new SDLRenderer;
	eventer = new SDLEventManager;

	renderer->Init();

}

GameStateManager::~GameStateManager()
{
	renderer->ShutDown();
}

void GameStateManager::Update()
{
	eventer->Update( quit, pause, deltaTime );
	stateMachine->Update( deltaTime, eventer );

	// RENDER
	renderer->StartRender();
	stateMachine->Render( renderer, SDLFontManager::GetInstance() );
	renderer->EndRender();
}

bool GameStateManager::Quit() const
{
	return quit;
}

bool GameStateManager::IsPaused() const
{
	return pause;
}