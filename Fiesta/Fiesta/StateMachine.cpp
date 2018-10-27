/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "StateMachine.h"

#include "Crowd.h"

State::State( BaseObject* _parent )
	: parent( _parent )
{

}

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
		currentState->Update( _dt );
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

Move::Move( BaseObject* _parent )
	: State( _parent )
{

}

void Move::Enter()
{

}

void Move::Update( const float _dt )
{

}

void Move::Exit()
{

}

void Move::Speed( float _speed )
{
	speed = _speed;
}