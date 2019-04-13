/* GLM Studio @ copyright 2018 */

#pragma once

class Crowd;
class State;
class FontManager;

class CrowdManager
{
public:
	static const Vector2 seatsInitialPosition[ 3 ];

	static CrowdManager* GetInstance();
	~CrowdManager();

	void Add( const Vector2&, float, int );
	void Update( const float, EventManager* );
	void Render( Renderer*, FontManager* );
	void RenderDebug( Renderer*, FontManager* );
	void ShutDown();

	void HandleEvents( const Event& );

	State* IAmArrived( Crowd* );

	Crowd* GetFirstCrowd( int ) const;
	void GetQueueInfo( Crowd*, int&, int& );

	Vector2 GetTarget( Crowd* );

private:
	CrowdManager();
	CrowdManager( const CrowdManager& ) = delete;
	CrowdManager& operator=( const CrowdManager& ) = delete;

	void ClearSeats( Crowd* _dude );

	std::vector< Crowd* >		crowd;
	std::vector< Crowd* >		seats[ 3 ];
	float						timer = 0.0f;
};