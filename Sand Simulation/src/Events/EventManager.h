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

	/*static Event MouseDownEvent()
	{
		return GetInstance()._mouseDownEvent;
	}*/

	Event<int, int> MouseButtonPressedEvent;
	//Event<int, int> MouseButtonReleasedEvent;

	// Event KeyDownEvent;
	// Event KeyUpEvent;

private:
	EventManager()
	{
		MouseButtonPressedEvent = Event<int, int>();
		//MouseButtonReleasedEvent = Event();
	}

	

	
};