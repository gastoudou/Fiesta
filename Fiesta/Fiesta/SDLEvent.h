#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Event.h"

class SDLEvent : public Event
{
	friend class SDLEventManager;

public:
	virtual bool ClicLeft() const override
	{
		return events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT;
	}

	virtual bool ClicRight() const override
	{
		return events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_RIGHT;
	}

	virtual Vector2 Motion() const override
	{
		return Vector2( ( float )events.motion.x, ( float )events.motion.y );
	}

private:
	SDL_Event events;
};

class SDLEventManager : public EventManager
{
public:

	void Update( bool& _quit, bool& _pause, float& _deltaTime )
	{
		while ( SDL_PollEvent( &events.events ) != 0 )
		{
			const Uint8* keyboardState = SDL_GetKeyboardState( NULL );

			if ( events.events.type == SDL_QUIT )
			{
				_quit = true;
			}

			if ( events.events.type == SDL_KEYDOWN || events.events.type == SDL_KEYUP )
			{
				if ( keyboardState[ SDL_SCANCODE_ESCAPE ] )
				{
					_quit = true;
				}
				if ( keyboardState[ SDL_SCANCODE_SPACE ] )
				{
					_pause = !_pause;
					if ( _pause )
						_deltaTime = 0.0f;
					else
						_deltaTime = FIXED_TIME_STAMP;
				}
			}
			
			ActionsManager::GetInstance()->HandleEvents( events );
		}
	}

	SDLEvent events;
};
