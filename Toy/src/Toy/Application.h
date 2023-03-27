#pragma once

#include "Core.h"

#include "Window.h"
#include "Toy/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Toy/ImGui/ImGuiLayer.h"

#include "Toy/Renderer/Shader.h"
#include "Toy/Renderer/Buffer.h"
#include "Toy/Renderer/VertexArray.h"

namespace Toy{
	class TOY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

