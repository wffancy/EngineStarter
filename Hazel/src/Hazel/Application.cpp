#include "hzpch.h"

#include "Application.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Log.h"
#include "Platform/macOS/macWindow.h"
#include "Window.h"

#include "GLFW/glfw3.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {
    
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher disptacher(e);
        disptacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnCloseEvent));
        
        HZ_CORE_INFO("{0}", e)
    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnCloseEvent(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

}
