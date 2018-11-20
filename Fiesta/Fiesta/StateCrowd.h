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

	virtual void Enter() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void Exit() override;

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

	virtual void Enter() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void Exit() override;

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

	virtual void Enter() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void Exit() override;

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

	virtual void Enter() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void Exit() override;

private:
	WaitOrder() = delete;
	WaitOrder( const WaitOrder& ) = delete;
	WaitOrder& operator=( const WaitOrder& ) = delete;

	float timer = 0.0f;
	float limitToWait = 1500.0f;
};

class WaitForYourTurn : public StateCrowd
{
public:
	WaitForYourTurn( Crowd* _parent );

	virtual void Enter() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void Exit() override;

private:
	WaitForYourTurn() = delete;
	WaitForYourTurn( const WaitForYourTurn& ) = delete;
	WaitForYourTurn& operator=( const WaitForYourTurn& ) = delete;
};

class Upset : public StateCrowd
{
public:
	Upset( Crowd* _parent );

	virtual void Enter() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void Exit() override;

private:
	Upset() = delete;
	Upset( const Upset& ) = delete;
	Upset& operator=( const Upset& ) = delete;
};