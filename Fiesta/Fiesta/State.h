/* GLM Studio @ copyright 2018 */

#pragma once

class BaseObject;

class State
{
public:
	State();
	virtual ~State();

	virtual void Enter() = 0;
	virtual void Update( const float _dt, EventManager* _eventer ) = 0;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) = 0;
	virtual void Exit() = 0;

private:
	State( const State& ) = delete;
	State& operator=( const State& ) = delete;
};