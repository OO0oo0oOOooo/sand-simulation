#pragma once

#include <string>

enum class EventType { 
    None = 0,
    WindowClose, WindowResize, WindowMoved, WindowFocus, WindowLostFocus,
    ApplicationTick, ApplicationUpdate, ApplicationRender,
    MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
    KeyDown, KeyUp, KeyHold
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
    //virtual const std::string GetName() const = 0;
    //virtual const EventCategory GetCategory() const = 0;

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

};

class WindowMoved : public Event
{
public:
    WindowMoved() {};

};

class WindowFocus : public Event
{
public:
	WindowFocus() {};

};

class WindowLostFocus : public Event
{
public:
	WindowLostFocus() {};

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
class KeyEvent : public Event
{
public:
	int GetKeyCode() const { return _keyCode; }

	virtual const EventCategory GetCategory() const override { return EventCategory::Keyboard; }

protected:
    KeyEvent(int keyCode) : _keyCode(keyCode) {}

    int _keyCode;
};

class KeyDown : public KeyEvent
{
public:
    KeyDown(int keyCode) : KeyEvent(keyCode) {};
};

class KeyHold : public KeyEvent
{
public:
    KeyHold(int keyCode) : KeyEvent(keyCode) {};
};

class KeyUp : public KeyEvent
{
public:
    KeyUp(int keyCode) : KeyEvent(keyCode) {};
};
#pragma endregion


#pragma region Mouse Events
class MouseMoved : public Event
{
public:
    MouseMoved(float x, float y) : _mouseX(x), _mouseY(y) {};

    inline float GetX() const { return _mouseX; }
    inline float GetY() const { return _mouseY; }

private:
    float _mouseX;
    float _mouseY;
};

class MouseScrolled : public Event
{
public:
    MouseScrolled(float x, float y) : _scrollX(x), _scrollY(y) {};

    inline float GetX() const { return _scrollX; }
	inline float GetY() const { return _scrollY; }

private:
    float _scrollX;
    float _scrollY;
};

class MouseButtonEvent : public Event
{
public:
    inline int GetMouseButton() const { return _button; }

protected:
    MouseButtonEvent(int button) : _button(button) {};
	int _button;
};

class MouseButtonDown : public MouseButtonEvent
{
public:
    MouseButtonDown() {};
};

class MouseButtonHold : public MouseButtonEvent
{
public:
    MouseButtonHold() {};
};

class MouseButtonUp : public MouseButtonEvent
{
public:
	MouseButtonUp() {};
};
#pragma endregion
