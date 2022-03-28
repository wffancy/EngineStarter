#pragma once

#include "Core.h"

namespace Hazel {
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
    };

    Application* CreateApplication();

}
