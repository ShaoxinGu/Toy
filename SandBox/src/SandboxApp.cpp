#include<Toy.h>

class Sandbox : public Toy::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Toy::Application* Toy::CreateApplication()
{
	return new Sandbox();
}