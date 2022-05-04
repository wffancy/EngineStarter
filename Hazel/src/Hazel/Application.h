#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

#include "Window.h"

#include "LayerStack.h"


namespace Hazel {
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        void OnEvent(Event& e);
        bool OnCloseEvent(WindowCloseEvent& e);
        
        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();

}
