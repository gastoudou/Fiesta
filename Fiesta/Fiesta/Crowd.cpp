/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Crowd.h"

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

void Crowd::Update( const float _dt )
{
	if ( stateMachine )
	{
		stateMachine->Update( _dt );
	}
}

void Crowd::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Rect fillRect = { ( int )position.x, ( int )position.y, ( int )size.x, ( int )size.y };
	SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( _renderer, &fillRect );

	if ( stateMachine )
	{
		stateMachine->Render( _renderer, _font );
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

void Crowd::Clic()
{
	isClicked = true;
}

bool Crowd::IsClicked() const
{
	return isClicked;
}

void Crowd::SetRemove()
{
	toRemove = true;
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

void CrowdManager::Add( const Vector2& _position, const Vector2& _size, float _speed, const Vector2& _target )
{
	Crowd* person = new Crowd( _position, _size, _speed, _target );
	person->Init();
	crowd.push_back( person );
}

void CrowdManager::Update( const float _dt )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		Add( Vector2( 50.0f, 0.0f ), Vector2( 150.0f, 50.0f ), 2.5f, seatsCopyAgain[ rand() % 3 ] );
		timer = 500.0f;
	}

	auto it = crowd.begin();
	for ( ; it != crowd.end(); )
	{
		( *it )->Update( _dt );
		if ( ( *it )->ToRemove() )
		{
			delete *it;
			it = crowd.erase( it );
			continue;
		}
		++it;
	}
}

void CrowdManager::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	for ( size_t i = 0; i < crowd.size(); ++i )
	{
		crowd[ i ]->Render( _renderer, _font );
	}
}

void CrowdManager::HandleEvents( const SDL_Event& _event )
{
	if ( _event.type == SDL_MOUSEBUTTONDOWN )
	{
		if ( _event.button.button == SDL_BUTTON_LEFT )
		{
			int mouseX = _event.motion.x;
			int mouseY = _event.motion.y;

			for ( size_t i = 0; i < crowd.size(); ++i )
			{
				Crowd* current = crowd[ i ];

				if ( ( current->position.x < _event.motion.x && current->position.x + current->size.x > _event.motion.x )
					&& ( current->position.y < _event.motion.y && current->position.y + current->size.y > _event.motion.y ) )
				{
					current->Clic();
				}
			}
		}
	}
}