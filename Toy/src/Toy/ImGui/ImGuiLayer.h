#pragma once

#include "Toy/Layer.h"
#include "Toy/Events/ApplicationEvent.h"
#include "Toy/Events/MouseEvent.h"
#include "Toy/Events/KeyEvent.h"

namespace Toy {

	class TOY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}