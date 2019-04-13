/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "StateCrowd.h"

#include "Crowd.h"
#include "CrowdManager.h"
#include "ActionsManager.h"

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

void Move::Update( const float _dt, EventManager* /*_eventer*/ )
{
	Vector2 direction = parent->target - parent->position;
	direction.Normalize();
	parent->direction = direction;

	Vector2 newPosition = parent->position + direction * speed * _dt;
	parent->position = newPosition;

	Vector2 between = parent->target - parent->position;
	if ( between.LenSquared() < 5.0f )
	{
		parent->ChangeState( CrowdManager::GetInstance()->IAmArrived( parent ) );
	}
}

void Move::Render( Renderer*, FontManager* )
{

}

void Move::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 10, 255, 0, 0, "State: MOVE", _fonter->Small() );
	_renderer->DrawFillRect( ( int )parent->target.x, ( int )parent->target.y, 5, 5, 255, 0, 0, 255 );
	if ( parent && parent->festayreTexture )
	{
		_renderer->DrawOutlineRect( ( int )parent->position.x, ( int )parent->position.y, parent->festayreTexture->Width(), parent->festayreTexture->Height(), 255, 0, 0, 255 );
	}
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
	timer = 0.0f;
}

void Idle::Update( const float _dt, EventManager* /*_eventer*/ )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		parent->SetRemove();
	}
}

void Idle::Render( Renderer*, FontManager* )
{
}

void Idle::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawText( ( int )parent->Position().x + 10, ( int )parent->Position().y + 10, 255, 0, 0, "State: IDLE", _fonter->Small() );
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

	int orderSize = 1 + rand() % 2;
	for ( int i = 0; i < orderSize; ++i )
	{
		parent->order.push_back( rand() % ActionsManager::GetInstance()->GetNbActionsSelected() );
	}
}

void PlaceOrder::Update( const float _dt, EventManager* /*_eventer*/ )
{
	timer -= _dt;
	if ( timer < 0.0f )
	{
		parent->ChangeState( new WaitOrder( parent ) );
	}
}

void PlaceOrder::Render( Renderer* _renderer, FontManager* )
{
	for ( size_t i = 0; i < parent->GetOrder().size(); ++i )
	{
		Texture* sprite = ActionsManager::GetInstance()->GetOrderSprite( parent->GetOrder()[ i ] );
		int w = sprite->Width() / 2;
		int h = sprite->Height() / 2;
		_renderer->DrawSprite( sprite, ( int )parent->position.x + w * ( int )i, ( int )parent->position.y, w, h, 1.0f );
	}
}

void PlaceOrder::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 10, 255, 0, 0, "State: PLACE ORDER", _fonter->Small() );

	for ( size_t i = 0; i < parent->GetOrder().size(); ++i )
	{
		std::stringstream oss;
		oss << "order" << parent->GetOrder()[ i ];
		_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 20 + 10 * ( int )i, 0, 0, 0, oss.str().c_str(), _fonter->Small() );
	}
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
	parent->isWaiting = true;
}

void WaitOrder::Update( const float _dt, EventManager* /*_eventer*/ )
{
	timer += _dt;

	if ( timer > limitToWait )
	{
		parent->ChangeState( new Upset( parent ) );
		return;
	}

	if ( parent->IsServed() )
	{
		parent->ChangeState( new Idle( parent ) );
	}
}

void WaitOrder::Render( Renderer* _renderer, FontManager* )
{
	for ( size_t i = 0; i < parent->GetOrder().size(); ++i )
	{
		Texture* sprite = ActionsManager::GetInstance()->GetOrderSprite( parent->GetOrder()[ i ] );
		int w = sprite->Width() / 2;
		int h = sprite->Height() / 2;
		_renderer->DrawSprite( sprite, ( int )parent->position.x + w * ( int )i, ( int )parent->position.y, w, h, 1.0f );
	}
}

void WaitOrder::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 10, 255, 0, 0, "State: WAIT ORDER", _fonter->Small() );

	for ( size_t i = 0; i < parent->GetOrder().size(); ++i )
	{
		std::stringstream oss;
		oss << "order" << parent->GetOrder()[ i ];
		_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 20 + 10 * ( int )i, 0, 0, 0, oss.str().c_str(), _fonter->Small() );
	}
}

void WaitOrder::Exit()
{
	parent->isWaiting = false;
}

WaitForYourTurn::WaitForYourTurn( Crowd* _parent )
	: StateCrowd( _parent )
{

}

void WaitForYourTurn::Enter()
{

}

void WaitForYourTurn::Update( const float /*_dt*/, EventManager* /*_eventer*/ )
{
	parent->RefreshTarget();
}

void WaitForYourTurn::Render( Renderer*, FontManager* )
{
}

void WaitForYourTurn::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 10, 255, 0, 0, "State: WAIT FOR MY TURN...", _fonter->Small() );
}

void WaitForYourTurn::Exit()
{

}


Upset::Upset( Crowd* _parent )
	: StateCrowd( _parent )
{

}

void Upset::Enter()
{

}

void Upset::Update( const float _dt, EventManager* /*_eventer*/ )
{
	static float timer = 0.0f;
	timer += _dt;
	if ( timer > 250.0f )
		parent->ChangeState( new Idle( parent ) );
}

void Upset::Render( Renderer*, FontManager* )
{

}

void Upset::RenderDebug( Renderer* _renderer, FontManager* _fonter )
{
	_renderer->DrawText( ( int )parent->position.x + 10, ( int )parent->position.y + 10, 255, 0, 0, "State: UPSET...", _fonter->Small() );
}

void Upset::Exit()
{

}