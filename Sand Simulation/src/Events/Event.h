#pragma once

#include <vector>
#include <memory>

using EventHandler = void(*)();

class Event {
    std::vector<std::unique_ptr<EventHandler>> Handlers;

public:
    void NotifyHandlers();
    void AddHandler(const EventHandler& handler);
    void RemoveHandler(const EventHandler& handler);

    void operator()();
    Event& operator+=(const EventHandler& handler);
    Event& operator-=(const EventHandler& handler);
};



//
//#include <string>
//
//enum class EventType { 
//    None = 0,
//    WindowClose, WindowResize, WindowMoved, WindowFocus, WindowLostFocus,
//    ApplicationTick, ApplicationUpdate, ApplicationRender,
//    MouseMoved, MouseScrolled, MouseButtonDown, MouseButtonHold, MouseButtonUp,
//    KeyDown, KeyUp, KeyHold
//};
//
//enum class EventCategory { 
//    None, 
//    Input,
//    Window,
//    Mouse,
//    Keyboard, 
//    Application 
//};
//
//class Event {
//public:
//    virtual ~Event() = default;
//
//    bool GetHandled() const { return _handled; }
//    void SetHandled() { _handled = true; }
//
//    virtual const EventType GetType() const = 0;
//    //virtual const std::string GetName() const = 0;
//    //virtual const EventCategory GetCategory() const = 0;
//
//private:
//    bool _handled = false;
//};
//
//class EventDispatcher {
//public:
//	EventDispatcher(Event& event) : _event(event) {}
//
//	template<typename T, typename F>
//	bool Dispatch(const F& func) {
//		if (_event.GetType() == T::GetStaticType()) {
//			_event.SetHandled();
//			func(static_cast<T&>(_event));
//			return true;
//		}
//		return false;
//	}
//
//private:
//    Event& _event;
//};
//
//#pragma region Window Events
//class WindowClose : public Event
//{
//public:
//    WindowClose() {};
//};
//
//class WindowResize : public Event
//{
//public:
//	WindowResize(int x, int y) : _width(x), _height(y) {};
//
//    inline int GetSizeX() const { return _width; }
//    inline int GetSizeY() const { return _height; }
//
//private:
//    int _width;
//	int _height;
//};
//
//class WindowMoved : public Event
//{
//public:
//    WindowMoved() {};
//
//};
//
//class WindowFocus : public Event
//{
//public:
//	WindowFocus() {};
//
//};
//
//class WindowLostFocus : public Event
//{
//public:
//	WindowLostFocus() {};
//
//};
//
//
//
//#pragma endregion
//
//
//#pragma region Application Events
//class ApplicationTick : public Event
//{
//public:
//    ApplicationTick() {};
//    ~ApplicationTick() {};
//};
//
//class ApplicationUpdate : public Event
//{
//public:
//    ApplicationUpdate() {};
//    ~ApplicationUpdate() {};
//};
//
//class ApplicationRender : public Event
//{
//public:
//    ApplicationRender() {};
//    ~ApplicationRender() {};
//};
//#pragma endregion
//
//
//#pragma region Key Events
//class KeyEvent : public Event
//{
//public:
//	int GetKeyCode() const { return _keyCode; }
//
//	//  virtual const EventCategory GetCategory() const override { return EventCategory::Keyboard; }
//
//protected:
//    KeyEvent(int keyCode) : _keyCode(keyCode) {}
//
//    int _keyCode;
//};
//
//class KeyDown : public KeyEvent
//{
//public:
//    KeyDown(int keyCode) : KeyEvent(keyCode) {};
//};
//
//class KeyHold : public KeyEvent
//{
//public:
//    KeyHold(int keyCode) : KeyEvent(keyCode) {};
//};
//
//class KeyUp : public KeyEvent
//{
//public:
//    KeyUp(int keyCode) : KeyEvent(keyCode) {};
//};
//#pragma endregion
//
//
//#pragma region Mouse Events
//class MouseMoved : public Event
//{
//public:
//    MouseMoved(float x, float y) : _mouseX(x), _mouseY(y) {};
//
//    inline float GetX() const { return _mouseX; }
//    inline float GetY() const { return _mouseY; }
//
//private:
//    float _mouseX;
//    float _mouseY;
//};
//
//class MouseScrolled : public Event
//{
//public:
//    MouseScrolled(float x, float y) : _scrollX(x), _scrollY(y) {};
//
//    inline float GetX() const { return _scrollX; }
//	inline float GetY() const { return _scrollY; }
//
//private:
//    float _scrollX;
//    float _scrollY;
//};
//
//class MouseButtonEvent : public Event
//{
//public:
//    inline int GetMouseButton() const { return _button; }
//
//    inline float GetX() const { return _x; }
//    inline float GetY() const { return _y; }
//
//	//  virtual const EventCategory GetCategory() const override { return EventCategory::Mouse; }
//
//
//protected:
//    MouseButtonEvent(int button, float x, float y) : _button(button), _x(x), _y(y) {};
//	int _button;
//    float _x;
//    float _y;
//};
//
//class MouseButtonDown : public MouseButtonEvent
//{
//public:
//    MouseButtonDown(int button, float x, float y) : MouseButtonEvent(button, x, y) {};
//};
//
//class MouseButtonHold : public MouseButtonEvent
//{
//public:
//    MouseButtonHold(int button, float x, float y) : MouseButtonEvent(button, x, y) {};
//};
//
//class MouseButtonUp : public MouseButtonEvent
//{
//public:
//	MouseButtonUp(int button, float x, float y) : MouseButtonEvent(button, x, y) {};
//};
//#pragma endregion
