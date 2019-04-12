/* GLM Studio @ copyright 2018 */

#pragma once

class BaseObject
{
public:
	BaseObject( const Vector2& _position, const Vector2& _direction )
		: initposition( _position )
		, position( _position )
		, direction( _direction )
	{
		direction.Normalize();
	}

	BaseObject( const BaseObject& _copy )
	{
		position = _copy.position;
		direction = _copy.direction;
	}

	virtual void		Init() = 0;
	virtual void		Update( const float _dt, EventManager* _eventer ) = 0;
	virtual void		Render( Renderer* _renderer, FontManager* _fonter ) = 0;
	virtual void		RenderDebug( Renderer* _renderer, FontManager* _fonter ) = 0;
	virtual void		ShutDown() = 0;
	virtual int			Width() const = 0;
	virtual int			Height() const = 0;

	const Vector2& Position() const
	{
		return position;
	}

protected:
	Vector2				initposition;
	Vector2				position;
	Vector2				direction;

	BaseObject& operator=( const BaseObject& ) = delete;
};