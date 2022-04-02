#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

#include "Window.h"


namespace Hazel {
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
        
        void OnEvent(Event& e);
        bool OnCloseEvent(WindowCloseEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();

}
