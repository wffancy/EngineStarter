#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {
    }
    
    void OnUpdate() override
    {
        HZ_INFO("ExampleLayer::Update");
    }
    
    void OnEvent(Hazel::Event &event) override
    {
        
    }
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        PushLayer(new Hazel::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
    
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}
