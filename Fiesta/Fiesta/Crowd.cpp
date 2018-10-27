/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

#include "StateMachine.h"

Crowd::Crowd( const Vector2& _position, float _speed, const Vector2& _target )
	: BaseObject( _position, Vector2( _target - _position ) )
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

void Crowd::Update( const float _dt )
{
	if ( stateMachine )
	{
		stateMachine->Update( _dt );
	}
}

void Crowd::Render( SDL_Renderer* _renderer )
{
	SDL_Rect fillRect = { ( int )position.x, ( int )position.y, 50, 50 };
	SDL_SetRenderDrawColor( _renderer, 0x55, 0x55, 0x55, 0xFF );
	SDL_RenderFillRect( _renderer, &fillRect );

	/*SDL_Rect targetRect = { ( int )target.x, ( int )target.y, 5, 5 };
	SDL_SetRenderDrawColor( _renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( _renderer, &targetRect );

	SDL_SetRenderDrawColor( _renderer, 0xFF, 0x00, 0xFF, 0x00 );
	SDL_RenderDrawLine( _renderer, ( int )position.x, ( int )position.y, ( int )position.x + ( int )( direction.x * 15.0f ), ( int )position.y + ( int )( direction.y * 15.0f ) );
	*/
}

void Crowd::ShutDown()
{

}

bool Crowd::IsArrived() const
{
	Vector2 between = target - position;
	return between.LenSquared() < 1.0f;
}

CrowdManager::CrowdManager()
{

}

CrowdManager* CrowdManager::GetInstance()
{
	static CrowdManager instance;
	return &instance;
}

CrowdManager::~CrowdManager()
{
	for ( size_t i = 0; i < crowd.size(); ++i )
	{
		delete crowd[ i ];
		crowd[ i ] = nullptr;
	}
}

void CrowdManager::Add( const Vector2& _position, float _speed, const Vector2& _target )
{
	Crowd* person = new Crowd( _position, _speed, _target );
	person->Init();
	crowd.push_back( person );
}

void CrowdManager::Update( const float _dt )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		Add( Vector2( 50.0f, 0.0f ), 2.5f, seatsCopyAgain[ rand() % 3 ] );
		timer = 100.0f;
	}

	auto it = crowd.begin();
	for ( ; it != crowd.end(); )
	{
		( *it )->Update( _dt );
		if ( ( *it )->IsArrived() )
		{
			delete *it;
			it = crowd.erase( it );
			continue;
		}
		++it;
	}
}

void CrowdManager::Render( SDL_Renderer* _renderer )
{
	for ( size_t i = 0; i < crowd.size(); ++i )
	{
		crowd[ i ]->Render( _renderer );
	}
}