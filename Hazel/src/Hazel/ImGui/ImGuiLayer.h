//
//  ImGuiLayer.h
//  Hazel
//
//  Created by wufanfan on 2022/5/3.
//

#ifndef ImGuiLayer_h
#define ImGuiLayer_h

#include "Hazel/Layer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();
    
    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event& event);
private:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(MouseMovedEvent& e);
    bool OnMouseScrolledEvent(MouseScrolledEvent& e);
    bool OnKeyPressedEvent(KeyPressedEvent& e);
    bool OnKeyReleasedEvent(KeyReleasedEvent& e);
    bool OnKeyTypedEvent(KeyTypedEvent& e);
    bool OnWindowResizeEvent(WindowResizeEvent& e);
private:
    float m_Time = 0.0f;
};

}

#endif /* ImGuiLayer_h */
