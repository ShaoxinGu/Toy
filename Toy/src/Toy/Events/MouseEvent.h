#pragma once

#include "Toy/Events/Event.h"

#include <sstream>

namespace Toy
{
	class TOY_API MouseMovedEvent : public Event
	{
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent:" << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class TOY_API MouseScrolledEvent : public Event
	{
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent:" << m_XOffset << "," << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class TOY_API MouseButtonEvent : public Event
	{
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
	protected:
		MouseScrolledEvent(int button)
			: m_Button(button) {}
		int m_Button;
	};

	class TOY_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringsteam ss;
			ss << "MouseButtonPressedEvent:" << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
	};

	class TOY_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringsteam ss;
			ss << "MouseButtonReleasedEvent:" << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
	};
}