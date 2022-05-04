//
//  ImGuiLayer.cpp
//  Hazel
//
//  Created by wufanfan on 2022/5/3.
//

#include "hzpch.h"

#include "ImGuiLayer.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "glad/glad.h"
#include "Core.h"

namespace Hazel {

ImGuiLayer::ImGuiLayer() : Layer("ImGui")
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    
    const char* s = (char*)glGetString(GL_VERSION);
    printf("%s", s);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
    
}

void ImGuiLayer::OnUpdate()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    
    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event &event)
{
    EventDispatcher dispatch(event);
    dispatch.Dispatch<MouseButtonPressedEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatch.Dispatch<MouseButtonReleasedEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatch.Dispatch<MouseMovedEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatch.Dispatch<MouseScrolledEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatch.Dispatch<KeyPressedEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatch.Dispatch<KeyReleasedEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatch.Dispatch<KeyTypedEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    dispatch.Dispatch<WindowResizeEvent>(BIND_HAZEL_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(Hazel::MouseButtonPressedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;
    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(Hazel::MouseButtonReleasedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = false;
    return false;
}

bool ImGuiLayer::OnMouseMovedEvent(Hazel::MouseMovedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());
    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(Hazel::MouseScrolledEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.GetXOffset();
    io.MouseWheel += e.GetYOffset();
    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(Hazel::KeyPressedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = true;
    
    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_LEFT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(Hazel::KeyReleasedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = false;
    return false;
}

bool ImGuiLayer::OnWindowResizeEvent(Hazel::WindowResizeEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0, 1.0);
    glViewport(0, 0, e.GetWidth(), e.GetHeight());
    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(Hazel::KeyTypedEvent &e) {
    ImGuiIO& io = ImGui::GetIO();
    unsigned int keycode = e.GetKeyCode();
    if(keycode > 0 && keycode < 0x10000) {
        io.AddInputCharacter(keycode);
    }
    return false;
}

}
