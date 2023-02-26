#include "toypch.h"
#include <Toy.h>

class ExampleLayer : public Toy::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{	
	}

	void OnUpdate() override
	{
		// TOY_INFO("ExampleLayer::Update");
	}

	void OnEvent(Toy::Event& event) override
	{
		//TOY_TRACE("{0}", event);
	}
};

class Sandbox : public Toy::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Toy::Application* Toy::CreateApplication()
{
	return new Sandbox();
}