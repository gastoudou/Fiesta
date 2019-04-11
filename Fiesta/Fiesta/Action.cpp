/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Action.h"

#include "SDLTexture.h"

#include "ActionsManager.h"
#include "MoneyManager.h"

Action::Action( const Vector2& _position, const Vector2& _size, const std::string& _path, int _row )
	: BaseObject( _position, _size, Vector2() )
	, path( _path )
	, row( _row )
{

}

Action::~Action()
{

}

void Action::Init()
{
	sprite = SDLTextureManager::GetInstance()->LoadTexture( path.c_str() );
}

void Action::Update( const float /*_dt*/, EventManager* /*_eventer*/ )
{

}

void Action::Render( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawFillRect( ( int )position.x, ( int )position.y, ( int )size.x, ( int )size.y, 0x00, 0x00, 0x00, 0xFF );
	_renderer->DrawOutlineRect( ( int )position.x, ( int )position.y, ( int )size.x, ( int )size.y, 0x00, 0xFF, 0x00, 0xFF );
	_renderer->DrawText( ( int )position.x + 10, ( int )position.y + 10, 255, 0, 0, path.c_str(), _fonter->Small() );
	_renderer->DrawSprite( sprite, ( int )position.x + 10, ( int )position.y + 10, 25, 40 );
}

void Action::ShutDown()
{
	SDLTextureManager::GetInstance()->FreeTexture( sprite );
}

void ActionSelect::Execute()
{
	ActionsManager::GetInstance()->AddToDesk( path.c_str() );
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