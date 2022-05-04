#include "hzpch.h"

#include "Application.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Log.h"
#include "Platform/macOS/macWindow.h"
#include "Window.h"

#include "glad/glad.h"

namespace Hazel {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_HAZEL_EVENT_FN(Application::OnEvent));
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
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_HAZEL_EVENT_FN(Application::OnCloseEvent));
        
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
