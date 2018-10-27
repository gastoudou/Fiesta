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
	{
		currentState->Update( _dt );
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

Move::Move( BaseObject* _parent, float _speed )
	: State( _parent )
	, speed( _speed )
{

}

void Move::Enter()
{

}

void Move::Update( const float _dt )
{
	Crowd* crowd = static_cast< Crowd* >( parent );
	Vector2 save_direction = crowd->direction;
	Vector2 save_position = crowd->position;

	crowd->position = save_position + save_direction * speed * _dt;
}

void Move::Exit()
{

}

void Move::Speed( float _speed )
{
	speed = _speed;
}

Idle::Idle( BaseObject* _parent )
	: State( _parent )
{

}

void Idle::Enter()
{

}

void Idle::Update( const float _dt )
{

}

void Idle::Exit()
{

}

OrderDrink::OrderDrink( BaseObject* _parent )
	: State( _parent )
{

}

void OrderDrink::Enter()
{

}

void OrderDrink::Update( const float _dt )
{

}

void OrderDrink::Exit()
{

}