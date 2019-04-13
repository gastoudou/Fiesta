/* GLM Studio @ copyright 2018 */

#pragma once

#include "Action.h"

class Crowd;
class Renderer;

class ActionsManager
{
public:
	static ActionsManager* GetInstance()
	{
		static ActionsManager instance;
		return &instance;
	}

	void Init();
	void Update( const float _dt, EventManager* _eventer );
	void Render( Renderer* _renderer, FontManager* _fonter );
	void RenderDebug( Renderer* _renderer, FontManager* _fonter );
	void ShutDown();

	void AddSelect( const Vector2& _position, const std::string _name );
	void AddServe( const Vector2& _position, const std::string _name, int _row );

	void AddToDesk( int _id );
	void RemoveFromDesk( Action* _action );

	int GetNbActionsSelected() const;
	const std::string& GetActionSelectedName( int _id ) const;

	Texture* GetOrderSprite( int _id ) const;

private:
	ActionsManager();
	~ActionsManager();

	void HandleEvents( const Event& _event );

	std::vector< Action* > actions;
	std::vector< Action* > actionsSelected;

	std::vector< int > desk;

	Texture* order[ 4 ] = { nullptr };

	bool canClic = true;
	int id = 0;
};