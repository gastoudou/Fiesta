/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

#include "StateMachine.h"

Crowd::Crowd( const Vector2& _position, const Vector2& _direction, float _speed )
	: BaseObject( _position, _direction )
	, speed( _speed )
{

}

Crowd::~Crowd()
{
	delete stateMachine;
	stateMachine = nullptr;
}

void Crowd::Init()
{
	stateMachine = new StateMachine;
	stateMachine->ChangeState( new Move( this ) );
}

void Crowd::Update( const float _dt )
{
	Vector2 save_direction = direction;

	position = position + save_direction * speed * _dt;
	position.DrawDebug( "crowd position" );

	if ( stateMachine )
	{
		stateMachine->Update( _dt );
	}
}

void Crowd::Render( SDL_Renderer* _renderer )
{
	SDL_Rect fillRect = { ( int )position.x, ( int )position.y, 10, 10 };
	SDL_SetRenderDrawColor( _renderer, 0xAA, 0x12, 0x34, 0xFF );
	SDL_RenderFillRect( _renderer, &fillRect );
}

void Crowd::ShutDown()
{

}