/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "GameStateManager.h"

#include "SDLFont.h"
#include "SDLRenderer.h"
#include "SDLEvent.h"
#include "SDLTexture.h"

#include "StateMachine.h"
#include "GameState.h"

GameStateManager::GameStateManager()
{
	srand( static_cast< unsigned int >( time( NULL ) ) );

	renderer = new SDLRenderer;
	eventer = new SDLEventManager;
	renderer->Init();

	SDLTextureManager::GetInstance()->Init( renderer );

	stateMachine = new StateMachine;
	stateMachine->ChangeState( new GameState_MainMenu( this ) );

	quit = false;
	deltaTime = EventManager::FIXED_TIME_STAMP; // @GSO: switch to engine calculated fps | maybe fixed? -> stick to 60fps
}

GameStateManager::~GameStateManager()
{
	renderer->ShutDown();

	delete stateMachine;
	delete eventer;
	delete renderer;
}

void GameStateManager::Update()
{
	eventer->Update( quit, pause, deltaTime );
	stateMachine->Update( deltaTime, eventer );
	renderer->StartRender();
	stateMachine->Render( renderer, SDLFontManager::GetInstance() );
#ifdef _DEBUG
	stateMachine->RenderDebug( renderer, SDLFontManager::GetInstance() );
#endif
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