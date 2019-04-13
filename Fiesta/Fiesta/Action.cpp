/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "Action.h"

#include "SDLTexture.h"

#include "ActionsManager.h"
#include "MoneyManager.h"
#include "SoundManager.h"

Action::Action( const Vector2& _position, const std::string& _path, int _row )
	: BaseObject( _position, Vector2() )
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

void Action::Render( Renderer* _renderer, FontManager* /*_fonter*/ )
{
	_renderer->DrawSprite( sprite, ( int )position.x - sprite->Width() / 2, ( int )position.y, sprite->Width(), sprite->Height() );
}

void Action::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawOutlineRect( ( int )position.x - sprite->Width() / 2, ( int )position.y, sprite->Width(), sprite->Height(), 0xFF, 0x00, 0xFF, 0xFF );
	_renderer->DrawText( ( int )position.x - sprite->Width() / 2, ( int )position.y + sprite->Height() / 2, 255, 0, 0, path.c_str(), _fonter->Small() );
}

void Action::ShutDown()
{
	SDLTextureManager::GetInstance()->FreeTexture( sprite );
}

int Action::Width() const
{
	return sprite->Width();
}

int Action::Height() const
{
	return sprite->Width();
}

const std::string& Action::GetPath() const
{
	return path;
}

const int Action::GetRow() const
{
	return row;
}

bool Action::ClicIn( const Vector2& motion ) const
{
	return ( int )position.x - sprite->Width() / 2 <= motion.x && ( int )position.x + sprite->Width() / 2 >= motion.x &&
		( int )position.y <= motion.y && ( int )position.y + sprite->Height() >= motion.y;
}

void Action::LoadSoundEffect( const std::string& _path )
{
	soundID = SoundManager::GetInstance()->LoadSound( _path.c_str() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ActionSelect::Execute()
{
	SoundManager::GetInstance()->PlaySound( soundID );
	ActionsManager::GetInstance()->AddToDesk( path.c_str() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ActionServe::Execute()
{
	SoundManager::GetInstance()->PlaySound( soundID );
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