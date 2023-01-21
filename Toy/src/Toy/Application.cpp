#include "toypch.h"
#include "Application.h"

#include "Toy/Events/ApplicationEvent.h"
#include "Toy/Log.h"

namespace Toy {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 700);
		if (e.IsInCategory(EventCategoryInput))
			TOY_TRACE(e);
		while (true);
	}
}

