/* GLM Studio @ copyright 2018 */

#pragma once

#include <SDL.h>

#include "Event.h"

#include "CrowdManager.h"
#include "ActionsManager.h"
#include "MoneyManager.h"

class SDLEvent : public Event
{
	friend class SDLEventManager;

public:
	virtual bool ClicLeft() const override;
	virtual bool ClicRight() const override;
	virtual Vector2 Motion() const override;

private:
	SDL_Event events = {};
};

class SDLEventManager : public EventManager
{
public:

	virtual void Update( bool& _quit, bool& _pause, float& _deltaTime ) override;
	virtual const Event& GetEvents() const override;

private:
	SDLEvent events;
};