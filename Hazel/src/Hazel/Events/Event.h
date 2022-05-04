//
//  Event.h
//  Hazel
//
//  Created by wufanfan on 2022/3/29.
//

#ifndef Event_h
#define Event_h

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

// 枚举类与枚举的不同
// 枚举类在声明与定义时需要限定作用域，即意味着在统一作用域下可以使用同一枚举名称
// 其次枚举类不可以被隐式转化为整型，但可以被显式转换
// 目前Hazel中的事件是阻塞等待触发的
enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped, 
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication    = BIT(0),
    EventCategoryInput          = BIT(1),
    EventCategoryKeyboard       = BIT(2),
    EventCategoryMouse          = BIT(3),
    EventCategoryMouseButton    = BIT(4)
};

// 用##操作后的结果必须是一个已经预定义过的符号(gcc)
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


class Event
{
    friend class EventDispatcher;
public:
    bool Handled = false;
    
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }
    
    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }
};

class EventDispatcher
{
    template<typename T>
    using EventFunc = std::function<bool(T&)>;
    
public:
    EventDispatcher(Event& event)
    : m_Event(event) {}
    
    template<typename T>
    bool Dispatch(EventFunc<T> func)
    {
        if(m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.Handled = func(*(T*)&m_Event);
            return true;
        }
        return false;
    }
    
private:
    Event& m_Event;
};


inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}

}
#endif /* Event_h */
