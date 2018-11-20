/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "CrowdManager.h"

#include "Crowd.h"
#include "StateCrowd.h"

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

void CrowdManager::Add( const Vector2& _position, const Vector2& _size, float _speed, int _target )
{
	Crowd* person = new Crowd( _position, _size, _speed, seatsInitialPosition[ _target ] - Vector2( 0, 55.0f * seats[ _target ].size() ) );
	person->Init();
	crowd.push_back( person );
	seats[ _target ].push_back( person );
}

void CrowdManager::Update( const float _dt )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		Add( Vector2( 50.0f, 0.0f ), Vector2( 150.0f, 50.0f ), 2.5f, rand() % 3 );
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

void CrowdManager::Render( Renderer* _renderer, FontManager* _fonter )
{
	for ( size_t i = 0; i < crowd.size(); ++i )
	{
		crowd[ i ]->Render( _renderer, _fonter );
	}
}

void CrowdManager::HandleEvents( const Event& /*_event*/ )
{

}

State* CrowdManager::IAmArrived( Crowd* _dude )
{
	for ( size_t j = 0; j < 3; ++j )
	{
		if ( !seats[ j ].empty() )
		{
			if ( seats[ j ].front() == _dude )
			{
				return new PlaceOrder( _dude );
			}
		}
	}
	return new WaitForYourTurn( _dude );
}

Crowd* CrowdManager::GetCrowd( int _row )
{
	if ( seats[ _row ].empty() ) return nullptr;

	Crowd* current = *seats[ _row ].begin();
	seats[ _row ].erase( seats[ _row ].begin() );
	return current;
}

Vector2 CrowdManager::GetTarget( Crowd* _dude )
{
	int row = 0;
	int turn = 0;
	GetQueueInfo( _dude, row, turn );
	return seatsInitialPosition[ row ] - Vector2( 0, 55.0f * turn );
}

void CrowdManager::GetQueueInfo( Crowd* _dude, int& row, int& turn )
{
	for ( size_t j = 0; j < 3; ++j )
	{
		for ( size_t i = 0; i < seats[ j ].size(); ++i )
		{
			if ( seats[ j ][ i ] == _dude )
			{
				row = ( int )j;
				turn = ( int )i;
				break;
			}
		}
	}
}