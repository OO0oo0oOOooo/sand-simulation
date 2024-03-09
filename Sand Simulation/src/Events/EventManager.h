#pragma once

#include "Event.h"

#include <iostream>

class EventManager
{
public:
	EventManager(const EventManager&) = delete;

	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	static Event MouseDownEvent()
	{
		return GetInstance()._mouseDownEvent;
	}

private:
	EventManager()
	{
		_mouseDownEvent = Event();
	}

	Event _mouseDownEvent;

	
};