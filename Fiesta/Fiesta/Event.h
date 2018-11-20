/* GLM Studio @ copyright 2018 */

#pragma once

class Event
{
public:
	virtual bool ClicLeft() const = 0;
	virtual bool ClicRight() const = 0;
	virtual Vector2 Motion() const = 0;
};

class EventManager
{
public:
	const static float FIXED_TIME_STAMP;

	virtual void Update( bool& quit, bool& pause, float& deltaTime ) = 0;
};