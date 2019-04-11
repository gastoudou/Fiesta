/* GLM Studio @ copyright 2018 */

#pragma once

#include "State.h"
class GameStateManager;

class GameState_MainMenu : public State
{
public:

	GameState_MainMenu( GameStateManager* _parent );
	virtual ~GameState_MainMenu();

	virtual void Enter();
	virtual void Update( const float _dt, EventManager* _eventer );
	virtual void Render( Renderer* _renderer, FontManager* _fonter );
	virtual void Exit();

private:
	GameState_MainMenu() = delete;

	Texture* bgTexture = nullptr;
	GameStateManager* parent = nullptr;
};

class GameState_Gameplay : public State
{
public:

	explicit GameState_Gameplay( GameStateManager* _parent );
	virtual ~GameState_Gameplay();

	virtual void Enter();
	virtual void Update( const float _dt, EventManager* _eventer );
	virtual void Render( Renderer* _renderer, FontManager* _fonter );
	virtual void Exit();

private:

	GameState_Gameplay() = delete;

	void RenderStatic( Renderer* _renderer );
	void DrawTitle( Renderer* _renderer );
	void DrawPause( Renderer* _renderer );

	Texture* bgFloorTexture = nullptr;
	Texture* bgWallsTexture = nullptr;
	Texture* pauseTexture = nullptr;
	Texture* barTexture = nullptr;
	Texture* shelfTexture = nullptr;
	Texture* barmanTexture = nullptr;
	GameStateManager* parent = nullptr;
};