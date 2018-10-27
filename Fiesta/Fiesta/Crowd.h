/* GLM Studio @ copyright 2018 */

#pragma once

class StateMachine;

class BaseObject
{
	friend class Move;

public:
	BaseObject( const Vector2& _position, const Vector2& _direction )
		: position( _position )
		, direction( _direction )
	{
		position.DrawDebug( "position" );
		direction.DrawDebug( "direction" );
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
	Vector2				position;
	Vector2				direction;

	BaseObject& operator=( const BaseObject& ) = delete;
};

class Crowd : public BaseObject
{
	friend class Move;

public:
	Crowd( const Vector2& _position, const Vector2& _direction, float _speed );

	virtual ~Crowd();

	virtual void Init();
	virtual void Update( const float _dt );
	virtual void Render( SDL_Renderer* _renderer );
	virtual void ShutDown();

private:
	Crowd() = delete;
	Crowd& operator=( const Crowd& ) = delete;

	StateMachine*		stateMachine = nullptr;
	float				speed = 0.0f;
};

class CrowdManager
{
public:

	static CrowdManager* GetInstance()
	{
		static CrowdManager instance;
		return &instance;
	}

	~CrowdManager()
	{
		for ( size_t i = 0; i < crowd.size(); ++i )
		{
			delete crowd[ i ];
			crowd[ i ] = nullptr;
		}
	}

	void Add( const Vector2& _position, const Vector2& _direction, float _speed )
	{
		Crowd* person = new Crowd( _position, _direction, _speed );
		person->Init();
		crowd.push_back( person );
	}

	void Update( const float _dt )
	{
		for ( size_t i = 0; i < crowd.size(); ++i )
		{
			crowd[ i ]->Update( _dt );
		}
	}
	void Render( SDL_Renderer* _renderer )
	{
		for ( size_t i = 0; i < crowd.size(); ++i )
		{
			crowd[ i ]->Render( _renderer );
		}
	}


private:
	CrowdManager() {}
	CrowdManager( const CrowdManager& ) = delete;
	CrowdManager& operator=( const CrowdManager& ) = delete;

	std::vector< Crowd* > crowd;
};