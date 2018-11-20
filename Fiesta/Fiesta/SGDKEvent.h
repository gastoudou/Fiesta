#pragma once
#include "stdafx.h"
#include <genesis.h>
#include "Event.h"

class SGDKEvent : public Event
{
	friend class SGDKEventManager;

public:
	virtual bool ClicLeft() const override
	{
		return false;
	}

	virtual bool ClicRight() const override
	{
		return false;
	}

	virtual Vector2 Motion() const override
	{
		return Vector2( 0.0f, 0.0f );
	}
};

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	// for jumps
}

class SGDKEventManager : public EventManager
{
public:

	SGDKEventManager()
	{
		JOY_init();
		JOY_setEventHandler( &myJoyHandler );
	}

	void Update( bool& _quit, bool& _pause, float& _deltaTime )
	{
		/*
		
		u16 value = JOY_readJoypad( JOY_1 );
		if ( value & BUTTON_UP ) posY--;
		else if ( value & BUTTON_DOWN ) posY++;
		if ( value & BUTTON_LEFT ) posX--;
		else if ( value & BUTTON_RIGHT ) posX++;

		*/
	}

	SGDKEvent events;
};