#pragma once

#include "Core.h"

namespace Toy{
	class TOY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

