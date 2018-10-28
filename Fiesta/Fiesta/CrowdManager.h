/* GLM Studio @ copyright 2018 */

#pragma once

class Crowd;
class State;

const Vector2 seatsInitialPosition[ 3 ] =
{
	Vector2( 0.0f, 590.0f ),
	Vector2( 180.0f, 590.0f ),
	Vector2( 360.0f, 590.0f )
};

class CrowdManager
{
public:
	static CrowdManager* GetInstance();
	~CrowdManager();

	void Add( const Vector2& _position, const Vector2& _size, float _speed, int _target );
	void Update( const float _dt );
	void Render( SDL_Renderer* _renderer, TTF_Font* _font );

	void HandleEvents( const SDL_Event& _event );

	State* IAmArrived( Crowd* );

	Crowd* GetCrowd( int _row );
	void GetQueueInfo( Crowd* _dude, int& _row, int& _turn );

	Vector2 GetTarget( Crowd* _dude );

private:
	CrowdManager();
	CrowdManager( const CrowdManager& ) = delete;
	CrowdManager& operator=( const CrowdManager& ) = delete;

	std::vector< Crowd* >		crowd;
	std::vector< Crowd* >		seats[ 3 ];
	float						timer = 0.0f;
};