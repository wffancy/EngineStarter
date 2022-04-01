//
//  macWindow.h
//  Hazel
//
//  Created by wufanfan on 2022/4/1.
//

#ifndef macWindow_h
#define macWindow_h

#include "Hazel/Window.h"

#include "GLFW/glfw3.h"

namespace Hazel {

class MacWindow : public Window {
public:
    MacWindow(const WindowProps& props);
    virtual ~MacWindow();
    
    void OnUpdate() override;
    
    inline unsigned int GetWidth() const override { return m_Data.Width; }
    inline unsigned int GetHeight() const override { return m_Data.Height; }
    
    // Window attributes
    inline void SetEventCallback(const EventCallbackFunc& callback) override { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;
    
private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();
private:
    GLFWwindow* m_Window;

    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        EventCallbackFunc EventCallback;
    };

    WindowData m_Data;
};


}

#endif /* macWindow_h */
