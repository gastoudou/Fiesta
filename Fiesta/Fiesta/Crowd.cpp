/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

#include "SDLRenderer.h"
#include "SDLTexture.h"

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
	festayreTexture = SDLTextureManager::GetInstance()->LoadTexture( "spClient.png" );

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
	_renderer->DrawSprite( festayreTexture, ( int )position.x, ( int )position.y - 45, 55/*( int )size.x*/, 90/*( int )size.y*/ );

	if ( stateMachine )
	{
		stateMachine->Render( _renderer, _fonter );
	}
}

void Crowd::ShutDown()
{
	SDLTextureManager::GetInstance()->FreeTexture( festayreTexture );
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