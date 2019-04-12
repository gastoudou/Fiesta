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
	friend class Upset;

public:
	Crowd( const Vector2& _position, float _speed, const Vector2& _target );

	virtual ~Crowd();

	virtual void Init() override;
	virtual void Update( const float _dt, EventManager* _eventer ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void RenderDebug( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void ShutDown() override;
	virtual int Width() const override;
	virtual int Height() const override;

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
	Texture*			festayreTexture = nullptr;
	Vector2				target;
	float				speed = 0.0f;
	bool				isServed = false;
	bool				toRemove = false;
	bool				isWaiting = false;

	std::vector< std::string > order;
};