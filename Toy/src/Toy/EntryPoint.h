#pragma once

#ifdef TOY_PLATFORM_WINDOWS

extern Toy::Application* Toy::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Toy::CreateApplication();
	app->Run();
	delete app;
}
#endif // TOY_PLATFORM_WINDOWS
