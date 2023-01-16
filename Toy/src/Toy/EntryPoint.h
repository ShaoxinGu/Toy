#pragma once

#ifdef TOY_PLATFORM_WINDOWS

extern Toy::Application* Toy::CreateApplication();

int main(int argc, char** argv)
{
	Toy::Log::Init();
	TOY_CORE_WARN("Initialized Log!");
	int a = 5;
	TOY_INFO("App Hello! Var={0}", a);
	TOY_CRITICAL("TOY_CRITICAL");

	auto app = Toy::CreateApplication();
	app->Run();
	delete app;
}
#endif // TOY_PLATFORM_WINDOWS
