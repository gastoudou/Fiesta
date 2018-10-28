/* GLM Studio @ copyright 2018 */

#pragma once

class State;
class StateMachine;

#include "BaseObject.h"

class Crowd : public BaseObject
{
	friend class Move;
	friend class PlaceOrder;
	friend class WaitOrder;
	friend class WaitForYourTurn;

public:
	Crowd( const Vector2& _position, const Vector2& _size, float _speed, const Vector2& _target );

	virtual ~Crowd();

	virtual void Init() override;
	virtual void Update( const float _dt ) override;
	virtual void Render( SDL_Renderer* _renderer, TTF_Font* _font ) override;
	virtual void ShutDown() override;

	void ChangeState( State* _newState );

	bool ToRemove() const;
	bool IsServed() const;
	bool IsWaiting() const;
	void Served();

	void SetRemove();

	const std::vector< std::string >& GetOrder() const;

private:
	Crowd() = delete;
	Crowd& operator=( const Crowd& ) = delete;

	void RefreshTarget();

	StateMachine*		stateMachine = nullptr;
	Vector2				target;
	float				speed = 0.0f;
	bool				isServed = false;
	bool				toRemove = false;
	bool				isWaiting = false;

	std::vector< std::string > order;
};