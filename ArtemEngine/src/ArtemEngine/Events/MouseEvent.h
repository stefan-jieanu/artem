#pragma once

#include "Event.h"

namespace ArtemEngine {

	class ARTEM_ENGINE_API MouseMovedEvent : public Event
	{
	public:
		// TODO: Change x, y to Vector2()
		MouseMovedEvent(float x, float y)
			: mouseX_(x), mouseY_(y) {}

		inline float GetX() const { return mouseX_; }
		inline float GetY() const { return mouseY_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX_ << ", " << mouseY_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouseX_, mouseY_;
	};

	class ARTEM_ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: xOffset_(xOffset), yOffset_(yOffset) {}

		inline float GetXOffset() const { return xOffset_; }
		inline float GetYOffset() const { return yOffset_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float xOffset_, yOffset_;
	};

	class ARTEM_ENGINE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return button_; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: button_(button) {}

		int button_;
	};

	class ARTEM_ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class ARTEM_ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
