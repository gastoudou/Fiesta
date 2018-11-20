/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "ActionsManager.h"

#include "CrowdManager.h"

ActionsManager::ActionsManager()
{

}

ActionsManager::~ActionsManager()
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		delete actions[ i ];
	}
}

void ActionsManager::AddSelect( const Vector2& _position, const Vector2& _size, const std::string _name )
{
	ActionSelect* action = new ActionSelect( _position, _size, _name );
	actions.push_back( action );
	actionsSelected.push_back( action );
}

void ActionsManager::AddServe( const Vector2& _position, const Vector2& _size, const std::string _name, int _row )
{
	actions.push_back( new ActionServe( _position, _size, _name, _row ) );
}

void ActionsManager::Update( const float _dt )
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->Update( _dt );
	}
}

void ActionsManager::Render( Renderer* _renderer, FontManager* _fonter )
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->Render( _renderer, _fonter );
	}

	// render desk
	for ( size_t i = 0; i < desk.size(); ++i )
	{
		_renderer->DrawText( 10, 730 + ( int )i * 10, 255, 0, 0, desk[ i ].c_str(), _fonter->Small() );
	}
}

void ActionsManager::HandleEvents( const Event& _event )
{
	if ( _event.ClicLeft() )
	{
		for ( size_t i = 0; i < actions.size(); ++i )
		{
			Action* current = actions[ i ];

			if ( ( current->position.x < _event.Motion().x && current->position.x + current->size.x > _event.Motion().x )
				&& ( current->position.y < _event.Motion().y && current->position.y + current->size.y > _event.Motion().y ) )
			{
				current->Execute();
			}
		}
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
		Crowd* current = CrowdManager::GetInstance()->GetCrowd( _action->row );
		if ( current && current->IsWaiting() )
		{
			static_cast< ActionServe* >( _action )->Serve( current, desk );
			desk.clear();
		}
	}
}