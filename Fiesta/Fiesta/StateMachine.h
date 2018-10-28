/* GLM Studio @ copyright 2018 */

#pragma once

class State;

class StateMachine
{
public:
	StateMachine() {}
	~StateMachine();

	void Update( const float _dt );
	void Render( SDL_Renderer* _renderer, TTF_Font* _font );

	void ChangeState( State* _state );

private:
	StateMachine( const StateMachine& ) = delete;
	StateMachine& operator=( const StateMachine& ) = delete;

	State*		currentState = nullptr;
};