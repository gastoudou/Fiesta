/* GLM Studio @ copyright 2018 */

#pragma once

class State;

class StateMachine
{
public:
	StateMachine() {}
	~StateMachine();

	void Update( const float _dt, EventManager* _eventer );
	void Render( Renderer* _renderer, FontManager* _fonter );

	void ChangeState( State* _state );

private:
	StateMachine( const StateMachine& ) = delete;
	StateMachine& operator=( const StateMachine& ) = delete;

	State*		currentState = nullptr;
};