/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "ActionsManager.h"

#include "CrowdManager.h"

ActionsManager::ActionsManager()
{

}

ActionsManager::~ActionsManager()
{

}

void ActionsManager::ShutDown()
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->ShutDown();
		delete actions[ i ];
		actions[ i ] = nullptr;
	}
}

void ActionsManager::AddSelect( const Vector2& _position, const std::string _name )
{
	ActionSelect* action = new ActionSelect( _position, _name );
	action->Init();
	actions.push_back( action );
	actionsSelected.push_back( action );
}

void ActionsManager::AddServe( const Vector2& _position, const std::string _name, int _row )
{
	ActionServe* action = new ActionServe( _position, _name, _row );
	action->Init();
	actions.push_back( action );
}

void ActionsManager::Update( const float _dt, EventManager* _eventer )
{
	HandleEvents( _eventer->GetEvents() );
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->Update( _dt, _eventer );
	}
}

void ActionsManager::Render( Renderer* _renderer, FontManager* _fonter )
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->Render( _renderer, _fonter );
	}
}

void ActionsManager::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->RenderDebug( _renderer, _fonter );
	}

	// render desk
	for ( size_t i = 0; i < desk.size(); ++i )
	{
		_renderer->DrawText( 10, 730 + ( int )i * 10, 255, 0, 0, desk[ i ].c_str(), _fonter->Small() );
	}
}

void ActionsManager::HandleEvents( const Event& _event )
{
	if ( _event.ClicLeft() && canClic )
	{
		for ( size_t i = 0; i < actions.size(); ++i )
		{
			Action* current = actions[ i ];

			if( current->ClicIn( _event.Motion() ) )
			{
				current->Execute();
			}
		}
		canClic = false;
	}

	if ( _event.ClicLeft() == false )
	{
		canClic = true;
	}
}

void ActionsManager::AddToDesk( const std::string _name )
{
	if ( desk.size() < 2 )
	{
		desk.push_back( _name );
	}
}

void ActionsManager::RemoveFromDesk( Action* _action )
{
	if ( !desk.empty() )
	{
		Crowd* current = CrowdManager::GetInstance()->GetCrowd( _action->GetRow() );
		if ( current && current->IsWaiting() )
		{
			static_cast< ActionServe* >( _action )->Serve( current, desk );
			desk.clear();
		}
	}
}

int ActionsManager::GetNbActionsSelected() const
{
	return ( int )actionsSelected.size();
}

const std::string& ActionsManager::GetActionSelectedName( int _id ) const
{
	return actionsSelected[ _id ]->GetPath();
}
