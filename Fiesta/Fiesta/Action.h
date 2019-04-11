/* GLM Studio @ copyright 2018 */

#pragma once

#include "Crowd.h"

class Texture;

class Action : public BaseObject
{
public:
	Action( const Vector2& _position, const Vector2& _size, const std::string& _path, int _row );
	~Action();

	virtual void Init() override;
	virtual void Update( const float _dt, EventManager* _eventer ) override;
	virtual void Render( Renderer* _renderer, FontManager* _fonter ) override;
	virtual void ShutDown() override;

	virtual void Execute() = 0;

	std::string path;
	int row = -1;

	Texture* sprite = nullptr;
};

class ActionSelect : public Action
{
public:
	ActionSelect( const Vector2& _position, const Vector2& _size, const std::string& _path, int _row = 0 )
		: Action( _position, _size, _path, _row )
	{

	}

	virtual void Execute() override;
};

class ActionServe : public Action
{
public:
	ActionServe( const Vector2& _position, const Vector2& _size, const std::string& _path, int _row )
		: Action( _position, _size, _path, _row )
	{

	}

	virtual void Execute() override;

	void Serve( Crowd* _dude, const std::vector< std::string >& _desk );
};