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

void ActionsManager::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	for ( size_t i = 0; i < actions.size(); ++i )
	{
		actions[ i ]->Render( _renderer, _font );
	}

	// render desk
	for ( size_t i = 0; i < desk.size(); ++i )
	{
		SDL_Color color = { 255, 0, 0 };
		SDL_Surface * surface = TTF_RenderText_Solid( _font, desk[ i ].c_str(), color );
		SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
		SDL_Rect dstrect = { 10, 730 + (int)i * 10, texW, texH };
		SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
		SDL_DestroyTexture( texture );
		SDL_FreeSurface( surface );
	}
}

void ActionsManager::HandleEvents( const SDL_Event& _event )
{
	if ( _event.type == SDL_MOUSEBUTTONDOWN )
	{
		if ( _event.button.button == SDL_BUTTON_LEFT )
		{
			for ( size_t i = 0; i < actions.size(); ++i )
			{
				Action* current = actions[ i ];

				if ( ( current->position.x < _event.motion.x && current->position.x + current->size.x > _event.motion.x )
					&& ( current->position.y < _event.motion.y && current->position.y + current->size.y > _event.motion.y ) )
				{
					current->Execute();
				}
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