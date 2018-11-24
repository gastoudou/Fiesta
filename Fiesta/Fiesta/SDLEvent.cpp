/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "SDLEvent.h"

bool SDLEvent::ClicLeft() const
{
	return events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT;
}

bool SDLEvent::ClicRight() const
{
	return events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_RIGHT;
}

Vector2 SDLEvent::Motion() const
{
	return Vector2( ( float )events.motion.x, ( float )events.motion.y );
}

void SDLEventManager::Update( bool& _quit, bool& _pause, float& _deltaTime )
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
	}
}

const Event& SDLEventManager::GetEvents() const
{
	return events;
}