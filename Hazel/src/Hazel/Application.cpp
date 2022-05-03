#include "hzpch.h"

#include "Application.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Log.h"
#include "Platform/macOS/macWindow.h"
#include "Window.h"

#include "Glad/glad.h"

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

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer: m_LayerStack)
                layer->OnUpdate();
            
            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher disptacher(e);
        disptacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnCloseEvent));
        
        HZ_CORE_INFO("{0}", e)
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled) break;
        }
    }

    bool Application::OnCloseEvent(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

}
