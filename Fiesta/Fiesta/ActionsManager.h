/* GLM Studio @ copyright 2018 */

#pragma once

#include "Action.h"

class Crowd;

class ActionsManager
{
public:
	static ActionsManager* GetInstance()
	{
		static ActionsManager instance;
		return &instance;
	}

	void Update( const float _dt );
	void Render( SDL_Renderer* _renderer, TTF_Font* _font );

	void AddSelect( const Vector2& _position, const Vector2& _size, const std::string _name );
	void AddServe( const Vector2& _position, const Vector2& _size, const std::string _name, int _row );
	void HandleEvents( const SDL_Event& _event );

	void AddToDesk( const std::string _name );
	void RemoveFromDesk( Action* _action );

	int GetNbActionsSelected() const
	{
		return actionsSelected.size();
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