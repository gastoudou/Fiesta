/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "CrowdManager.h"

#include "Crowd.h"
#include "StateCrowd.h"

const Vector2 CrowdManager::seatsInitialPosition[ 3 ] =
{
	Vector2( 135.0f, 610.0f ),
	Vector2( 270.0f, 610.0f ),
	Vector2( 405.0f, 610.0f )
};

CrowdManager::CrowdManager() = default;

CrowdManager* CrowdManager::GetInstance()
{
	static CrowdManager instance;
	return &instance;
}

CrowdManager::~CrowdManager() = default;

void CrowdManager::ShutDown()
{
	for ( size_t i = 0; i < crowd.size(); ++i )
	{
		crowd[ i ]->ShutDown();
		delete crowd[ i ];
		crowd[ i ] = nullptr;
	}
}

void CrowdManager::Add( const Vector2& _position, float _speed, int _target )
{
	Crowd* person = new Crowd( _position, _speed );
	seats[ _target ].push_back( person );
	crowd.push_back( person );
	person->Init();
}

void CrowdManager::Update( const float _dt, EventManager* _eventer )
{
	timer -= _dt;
	if ( timer < 0.0f && crowd.size() < 30 ) // max 30 dudes
	{
		Add( Vector2( 0.0f, 20.0f ), 2.5f, rand() % 3 );
		timer = 500.0f;
	}

	ClearSeats( nullptr );

	auto it = crowd.begin();
	for ( ; it != crowd.end(); )
	{
		Crowd* current = *it;

		if ( current->ToRemove() )
		{
			ClearSeats( current );
			current->ShutDown();
			delete current;
			current = nullptr;
			it = crowd.erase( it );
		}
		else
		{
			current->Update( _dt, _eventer );
			++it;
		}
	}
}

void CrowdManager::Render( Renderer* _renderer, FontManager* _fonter )
{
	for ( int i = ( int )crowd.size() - 1; i >= 0 ; --i )
	{
		crowd[ i ]->Render( _renderer, _fonter );
	}
}

void CrowdManager::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	for ( size_t i = 0; i < crowd.size(); ++i )
	{
		crowd[ i ]->RenderDebug( _renderer, _fonter );
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

Crowd* CrowdManager::GetFirstCrowd( int _row ) const
{
	if ( seats[ _row ].empty() )
	{
		return nullptr;
	}
	return *seats[ _row ].begin();
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
				return;
			}
		}
	}
}

void CrowdManager::ClearSeats( Crowd* _dude )
{
	for ( size_t j = 0; j < 3; ++j )
	{
		for ( size_t i = 0; i < seats[ j ].size(); ++i )
		{
			if ( seats[ j ][ i ] == _dude )
			{
				seats[ j ].erase( seats[ j ].begin() + i );
				return;
			}
		}
	}
}