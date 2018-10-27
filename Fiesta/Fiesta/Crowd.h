/* GLM Studio @ copyright 2018 */

#pragma once

class StateMachine;

const Vector2 seatsCopyAgain[ 3 ] = { Vector2( 0.0f, 590.0f ), Vector2( 180.0f, 590.0f ), Vector2( 360.0f, 590.0f ) };

class BaseObject
{
	friend class Move;

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
	virtual void		Update( const float _dt ) = 0;
	virtual void		Render( SDL_Renderer* _renderer ) = 0;
	virtual void		ShutDown() = 0;

protected:
	Vector2				initposition;
	Vector2				position;
	Vector2				direction;

	BaseObject& operator=( const BaseObject& ) = delete;
};

class Crowd : public BaseObject
{
	friend class Move;

public:
	Crowd( const Vector2& _position, float _speed, const Vector2& _target );

	virtual ~Crowd();

	virtual void Init();
	virtual void Update( const float _dt );
	virtual void Render( SDL_Renderer* _renderer );
	virtual void ShutDown();

	bool IsArrived() const;

private:
	Crowd() = delete;
	Crowd& operator=( const Crowd& ) = delete;

	StateMachine*		stateMachine = nullptr;
	Vector2				target;
	float				speed = 0.0f;
};

class CrowdManager
{
public:
	static CrowdManager* GetInstance();
	~CrowdManager();
	void Add( const Vector2& _position, float _speed, const Vector2& _target );
	void Update( const float _dt );
	void Render( SDL_Renderer* _renderer );

private:
	CrowdManager();
	CrowdManager( const CrowdManager& ) = delete;
	CrowdManager& operator=( const CrowdManager& ) = delete;

	std::vector< Crowd* >		crowd;
	float						timer = 0.0f;
};