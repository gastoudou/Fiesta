/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "StateCrowd.h"

#include "Crowd.h"

StateCrowd::StateCrowd( Crowd* _parent )
	: parent( _parent )
{

}

Move::Move( Crowd* _parent, float _speed )
	: StateCrowd( _parent )
	, speed( _speed )
{

}

void Move::Enter()
{

}

void Move::Update( const float _dt )
{
	Vector2 save_direction = parent->direction;
	Vector2 save_position = parent->position;

	parent->position = save_position + save_direction * speed * _dt;

	Vector2 between = parent->target - parent->position;
	if ( between.LenSquared() < 2.0f )
	{
		parent->ChangeState( new PlaceOrder( parent ) );
	}
}

void Move::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, "State: MOVE", color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { ( int )parent->position.x + 10, ( int )parent->position.y + 10, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void Move::Exit()
{

}

void Move::Speed( float _speed )
{
	speed = _speed;
}

Idle::Idle( Crowd* _parent )
	: StateCrowd( _parent )
{

}

void Idle::Enter()
{
	timer = 50.0f;
}

void Idle::Update( const float _dt )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		parent->SetRemove();
	}
}

void Idle::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, "State: IDLE", color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { ( int )parent->position.x + 10, ( int )parent->position.y + 10, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void Idle::Exit()
{

}

PlaceOrder::PlaceOrder( Crowd* _parent )
	: StateCrowd( _parent )
{

}

void PlaceOrder::Enter()
{
	timer = 50.0f;
}

void PlaceOrder::Update( const float _dt )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		parent->ChangeState( new WaitOrder( parent ) );
	}
}

void PlaceOrder::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, "State: PLACE ORDER", color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { ( int )parent->position.x + 10, ( int )parent->position.y + 10, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void PlaceOrder::Exit()
{

}

WaitOrder::WaitOrder( Crowd* _parent )
	: StateCrowd( _parent )
{

}

void WaitOrder::Enter()
{

}

void WaitOrder::Update( const float _dt )
{
	if ( parent->IsClicked() )
	{
		parent->ChangeState( new Idle( parent ) );
	}
}

void WaitOrder::Render( SDL_Renderer* _renderer, TTF_Font* _font )
{
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid( _font, "State: WAIT ORDER", color );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture( texture, NULL, NULL, &texW, &texH );
	SDL_Rect dstrect = { ( int )parent->position.x + 10, ( int )parent->position.y + 10, texW, texH };
	SDL_RenderCopy( _renderer, texture, NULL, &dstrect );
	SDL_DestroyTexture( texture );
	SDL_FreeSurface( surface );
}

void WaitOrder::Exit()
{

}