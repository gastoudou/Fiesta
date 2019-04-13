/* GLM Studio @ copyright 2018 */

#pragma once

#include "Crowd.h"

class Texture;

class Action : public BaseObject
{
public:
	Action( const Vector2&, const std::string&, int );
	~Action();

	virtual void Init() override;
	virtual void Update( const float, EventManager* ) override;
	virtual void Render( Renderer*, FontManager* ) override;
	virtual void RenderDebug( Renderer*, FontManager* ) override;
	virtual void ShutDown() override;

	virtual void Execute() = 0;

	virtual int Width() const override;
	virtual int Height() const override;

	const std::string& GetPath() const;
	const int GetRow() const;

	bool ClicIn( const Vector2& ) const;

protected:
	void LoadSoundEffect( const std::string& _path );

	Texture* sprite = nullptr;
	std::string path;
	int row = -1;
	int soundID = -1;
};

class ActionSelect : public Action
{
public:
	ActionSelect( const Vector2& _position, const std::string& _path, int _row = 0 )
		: Action( _position, _path, _row )
	{
		LoadSoundEffect( "resources/icecubes.wav" );
	}

	virtual void Execute() override;
};

class ActionServe : public Action
{
public:
	ActionServe( const Vector2& _position, const std::string& _path, int _row )
		: Action( _position, _path, _row )
	{
		//LoadSoundEffect( "resources/bell.wav" );
	}

	virtual void Execute() override;

	void Serve( Crowd* _dude, const std::vector< std::string >& _desk );
};