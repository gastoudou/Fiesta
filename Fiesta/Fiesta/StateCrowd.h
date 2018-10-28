/* GLM Studio @ copyright 2018 */

#pragma once

#include "State.h"

class Crowd;

class StateCrowd : public State
{
public:
	explicit StateCrowd( Crowd* _parent );

protected:
	Crowd*		parent = nullptr;

private:
	StateCrowd() = delete;
	StateCrowd( const StateCrowd& ) = delete;
	StateCrowd& operator=( const StateCrowd& ) = delete;
};

class Move : public StateCrowd
{
public:
	Move( Crowd* _parent, float _speed );

	virtual void Enter();
	virtual void Update( const float _dt );
	virtual void Render( SDL_Renderer* _renderer, TTF_Font* _font );
	virtual void Exit();

	void Speed( float _speed );

private:
	Move() = delete;
	Move( const Move& ) = delete;
	Move& operator=( const Move& ) = delete;

	float		speed = 0.0f;
};

class Idle : public StateCrowd
{
public:
	Idle( Crowd* _parent );

	virtual void Enter();
	virtual void Update( const float _dt );
	virtual void Render( SDL_Renderer* _renderer, TTF_Font* _font );
	virtual void Exit();

private:
	Idle() = delete;
	Idle( const Idle& ) = delete;
	Idle& operator=( const Idle& ) = delete;

	float timer = 50.0f;
};

class PlaceOrder : public StateCrowd
{
public:
	PlaceOrder( Crowd* _parent );

	virtual void Enter();
	virtual void Update( const float _dt );
	virtual void Render( SDL_Renderer* _renderer, TTF_Font* _font );
	virtual void Exit();

private:
	PlaceOrder() = delete;
	PlaceOrder( const PlaceOrder& ) = delete;
	PlaceOrder& operator=( const PlaceOrder& ) = delete;

	float timer = 0.0f;
};

class WaitOrder : public StateCrowd
{
public:
	WaitOrder( Crowd* _parent );

	virtual void Enter();
	virtual void Update( const float _dt );
	virtual void Render( SDL_Renderer* _renderer, TTF_Font* _font );
	virtual void Exit();

private:
	WaitOrder() = delete;
	WaitOrder( const WaitOrder& ) = delete;
	WaitOrder& operator=( const WaitOrder& ) = delete;
};