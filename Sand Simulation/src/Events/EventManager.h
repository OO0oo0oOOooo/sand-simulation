#pragma once

#include "Event.h"

class EventManager
{
public:
	EventManager(const EventManager&) = delete;
	EventManager() = default;

	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	Event<int, int, glm::vec2> MouseButtonEvent; // button: 0 = left, 1 = right | action: 1 = down, 0 = up | position: x, y
	Event<int, glm::vec2> MouseButtonDownEvent;
	Event<int, glm::vec2> MouseButtonUpEvent;
	Event<int> MouseButtonHeldEvent;
	Event<glm::vec2> MouseMoveEvent;

	Event<int> KeyDownEvent;
	Event<int> KeyUpEvent;

	Event<> WindowCloseEvent;

	Event<> UpdateWorldEvent;
	Event<int, int> UpdateChunkEvent;
};