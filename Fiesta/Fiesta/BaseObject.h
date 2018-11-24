/* GLM Studio @ copyright 2018 */

#pragma once

class BaseObject
{
	friend class Move;
	friend class Idle;
	friend class PlaceOrder;
	friend class WaitOrder;
	friend class WaitForYourTurn;

	friend class CrowdManager;
	friend class ActionsManager;

public:
	BaseObject( const Vector2& _position, const Vector2& _size, const Vector2& _direction )
		: initposition( _position )
		, position( _position )
		, size( _size )
		, direction( _direction )
	{
		direction.Normalize();
	}

	BaseObject( const BaseObject& _copy )
	{
		position = _copy.position;
		size = _copy.size;
		direction = _copy.direction;
	}

	virtual void		Init() = 0;
	virtual void		Update( const float _dt, EventManager* _eventer ) = 0;
	virtual void		Render( Renderer* _renderer, FontManager* _fonter ) = 0;
	virtual void		ShutDown() = 0;

protected:
	Vector2				initposition;
	Vector2				position;
	Vector2				direction;
	Vector2				size;

	BaseObject& operator=( const BaseObject& ) = delete;
};