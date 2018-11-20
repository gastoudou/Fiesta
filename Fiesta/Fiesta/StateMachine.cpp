/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "StateMachine.h"

#include "State.h"
#include "Crowd.h"

StateMachine::~StateMachine()
{
	if ( currentState )
	{
		currentState->Exit();
		delete currentState;
		currentState = nullptr;
	}
}

void StateMachine::Update( const float _dt )
{
	if ( currentState )
	{
		currentState->Update( _dt );
	}
}

void StateMachine::Render( Renderer* _renderer, FontManager* _fonter )
{
	if ( currentState )
	{
		currentState->Render( _renderer, _fonter );
	}
}

void StateMachine::ChangeState( State* _state )
{
	if ( currentState )
	{
		currentState->Exit();
		delete currentState;
		currentState = nullptr;
	}

	currentState = _state;

	if ( currentState )
		currentState->Enter();
}