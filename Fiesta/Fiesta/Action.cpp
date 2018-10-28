/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Action.h"

#include "ActionsManager.h"
#include "MoneyManager.h"

Action::Action( const Vector2& _position, const Vector2& _size, const std::string& _name, int _row )
	: BaseObject( _position, _size, Vector2() )
	, name( _name )
	, row( _row )
{

}

Action::~Action()
{

}

void Action::Init()
{

}

void Action::Update( const float _dt )
{

}

void Action::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Rect fillRect = { ( int )position.x, ( int )position.y, ( int )size.x, ( int )size.y };
	SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( _renderer, &fillRect );
	SDL_SetRenderDrawColor( _renderer, 0x00, 0xFF, 0x00, 0xFF );
	SDL_RenderDrawRect( _renderer, &fillRect );

	SDL_Color color = { 255, 0, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, name.c_str(), color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { ( int )position.x + 10, ( int )position.y + 10, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void Action::ShutDown()
{

}

void ActionSelect::Execute()
{
	ActionsManager::GetInstance()->AddToDesk( name.c_str() );
}

void ActionServe::Execute()
{
	ActionsManager::GetInstance()->RemoveFromDesk( this );
}

void ActionServe::Serve( Crowd* _dude, const std::vector< std::string >& _desk )
{
	int money = 5 * ( int )_dude->GetOrder().size();

	if ( _desk.size() == _dude->GetOrder().size() )
	{
		for ( size_t i = 0; i < _dude->GetOrder().size(); ++i )
		{
			if ( _dude->GetOrder()[ i ] != _desk[ i ] )
			{
				money = 0;
				break;
			}
		}
	}

	MoneyManager::GetInstance()->AddMoney( money );
	_dude->Served();
}