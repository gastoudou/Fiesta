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

	void Update( const float _dt, EventManager* _eventer );
	void Render( Renderer* _renderer, FontManager* _fonter );

	void AddSelect( const Vector2& _position, const Vector2& _size, const std::string _name );
	void AddServe( const Vector2& _position, const Vector2& _size, const std::string _name, int _row );
	void HandleEvents( const Event& _event );

	void AddToDesk( const std::string _name );
	void RemoveFromDesk( Action* _action );

	int GetNbActionsSelected() const
	{
		return ( int )actionsSelected.size();
	}

	const std::string& GetActionSelectedName( int _id )
	{
		return actionsSelected[ _id ]->name;
	}

private:
	ActionsManager();
	~ActionsManager();

	std::vector< Action* > actions;
	std::vector< Action* > actionsSelected;

	std::vector< std::string > desk;
};