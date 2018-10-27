/* GLM Studio @ copyright 2018 */

#pragma once

class BaseObject;

class State
{
public:
	explicit State( BaseObject* _parent );

	virtual void Enter() = 0;
	virtual void Update( const float _dt ) = 0;
	virtual void Exit() = 0;

protected:
	BaseObject*		parent = nullptr;

private:
	State() = delete;
	State( const State& ) = delete;
	State& operator=( const State& ) = delete;
};

class StateMachine
{
public:
	StateMachine() {}
	~StateMachine();

	void Update( const float _dt );
	void ChangeState( State* _state );

private:
	StateMachine( const StateMachine& ) = delete;
	StateMachine& operator=( const StateMachine& ) = delete;

	State*		currentState = nullptr;
};

class Move : public State
{
public:
	explicit Move( BaseObject* _parent );

	virtual void Enter();
	virtual void Update( const float _dt );
	virtual void Exit();

	void Speed( float _speed );

private:
	Move() = delete;
	Move( const Move& ) = delete;
	Move& operator=( const Move& ) = delete;

	float		speed = 0.0f;
};