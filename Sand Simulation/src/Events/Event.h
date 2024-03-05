#pragma once

#include <string>

enum class EventType { 
    None = 0,
    WindowClose, WindowResize, WindowMoved, WindowFocus, WindowLostFocus,
    ApplicationTick, ApplicationUpdate, ApplicationRender,
    MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
    KeyPressed, KeyReleased,
};

enum class EventCategory { 
    None, 
    Input,
    Window,
    Mouse,
    Keyboard, 
    Application 
};

class Event {
public:
    virtual ~Event() = default;

    bool GetHandled() const { return _handled; }
    void SetHandled() { _handled = true; }

    virtual const EventType GetType() const = 0;
    virtual const std::string GetName() const = 0;
    virtual const EventCategory GetCategory() const = 0;

private:
    bool _handled = false;
};

#pragma region Window Events
class WindowClose : public Event
{
public:
    WindowClose() {};
    ~WindowClose() {};
};

class WindowResize : public Event
{
public:
	WindowResize() {};
	~WindowResize() {};
};

class WindowMoved : public Event
{
public:
    WindowMoved() {};
    ~WindowMoved() {};
};

class WindowFocus : public Event
{
public:
	WindowFocus() {};
	~WindowFocus() {};
};

class WindowLostFocus : public Event
{
public:
	WindowLostFocus() {};
	~WindowLostFocus() {};
};



#pragma endregion


#pragma region Application Events
class ApplicationTick : public Event
{
public:
    ApplicationTick() {};
    ~ApplicationTick() {};
};

class ApplicationUpdate : public Event
{
public:
    ApplicationUpdate() {};
    ~ApplicationUpdate() {};
};

class ApplicationRender : public Event
{
public:
    ApplicationRender() {};
    ~ApplicationRender() {};
};
#pragma endregion


#pragma region Key Events
class KeyPressed : public Event
{
public:
    KeyPressed() {};
    ~KeyPressed() {};
};

class KeyReleased : public Event
{
public:
    KeyReleased() {};
    ~KeyReleased() {};
};
#pragma endregion


#pragma region Mouse Events
class MouseMoved : public Event
{
public:
    MouseMoved() {};
    ~MouseMoved() {};
};

class MouseScrolled : public Event
{
public:
    MouseScrolled() {};
    ~MouseScrolled() {};
};

class MouseButtonPressed : public Event
{
public:
    MouseButtonPressed() {};
    ~MouseButtonPressed() {};
};

class MouseButtonReleased : public Event
{
public:
	MouseButtonReleased() {};
	~MouseButtonReleased() {};
};
#pragma endregion
