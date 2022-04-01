#pragma once

#include "Core.h"
#include "Window.h"

namespace Hazel {
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();

}
