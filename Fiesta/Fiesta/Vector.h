/* GLM Studio @ copyright 2018 */

#pragma once

class Vector2
{
public:

	float x = 0.0f;
	float y = 0.0f;

	Vector2()
		: x( 0.0f )
		, y( 0.0f )
	{

	}

	Vector2( float _x, float _y )
		: x( _x )
		, y( _y )
	{

	}

	Vector2( const Vector2& _other )
		: x( _other.x )
		, y( _other.y )
	{

	}

	Vector2& operator=( const Vector2& _other )
	{
		x = _other.x;
		y = _other.y;
		return *this;
	}

	~Vector2()
	{

	}

	Vector2& operator*( float _f )
	{
		x *= _f;
		y *= _f;
		return *this;
	}

	const Vector2 operator+( const Vector2& _other ) const
	{
		return Vector2( this->x + _other.x, this->y + _other.y );
	}

	Vector2& operator+=( const Vector2& _other )
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}

	const Vector2 operator-( const Vector2& _other ) const
	{
		return Vector2( this->x - _other.x, this->y - _other.y );
	}

	Vector2& operator-=( const Vector2& _other )
	{
		x -= _other.x;
		y -= _other.y;
		return *this;
	}

	void DrawDebug( const char* _name ) const
	{
		std::cout << _name << ": " << x << ";" << y << std::endl;
	}

	float LenSquared() const
	{
		return x * x + y * y;
	}

	float Len() const
	{
		return sqrt( LenSquared() );
	}

	void Normalize()
	{
		if ( LenSquared() > 0.00001f )
		{
			const float len = Len();
			x /= len;
			y /= len;
		}
	}
};