/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

#include "CrowdManager.h"
#include "StateMachine.h"
#include "StateCrowd.h"

Crowd::Crowd( const Vector2& _position, const Vector2& _size, float _speed, const Vector2& _target )
	: BaseObject( _position, _size, Vector2( _target - _position ) )
	, target( _target )
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
	stateMachine->ChangeState( new Move( this, speed ) );
}

void Crowd::Update( const float _dt, EventManager* _eventer )
{
	if ( stateMachine )
	{
		stateMachine->Update( _dt, _eventer );
	}
}

void Crowd::Render( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawFillRect( ( int )target.x, ( int )target.y, ( int )size.x, ( int )size.y, 0xAB, 0xAA, 0xAA, 0xBB );
	_renderer->DrawFillRect( ( int )position.x, ( int )position.y, ( int )size.x, ( int )size.y, 0xFF, 0xFF, 0xFF, 0xFF );
	_renderer->DrawOutlineRect( ( int )position.x, ( int )position.y, ( int )size.x, ( int )size.y, 0xFF, 0x00, 0x00, 0xFF );

	if ( stateMachine )
	{
		stateMachine->Render( _renderer, _fonter );
	}
}

void Crowd::ShutDown()
{

}

void Crowd::ChangeState( State* _newState )
{
	stateMachine->ChangeState( _newState );
}

bool Crowd::ToRemove() const
{
	return toRemove;
}

bool Crowd::IsServed() const
{
	return isServed;
}

void Crowd::Served()
{
	isServed = true;
}

void Crowd::SetRemove()
{
	toRemove = true;
}

const std::vector< std::string >& Crowd::GetOrder() const
{
	return order;
}

bool Crowd::IsWaiting() const
{
	return isWaiting;
}

void Crowd::RefreshTarget()
{
	{
		Vector2 newTarget = CrowdManager::GetInstance()->GetTarget( this );

		if ( ( target - newTarget ).LenSquared() > 1.0f )
		{
			target = newTarget;
			stateMachine->ChangeState( new Move( this, speed ) );
		}
	}
}