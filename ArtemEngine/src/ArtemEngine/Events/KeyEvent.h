#pragma once

#include "Event.h"

#include <sstream>

namespace ArtemEngine {

	class ARTEM_ENGINE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyCode_; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode)
			: keyCode_(keycode) {}

		int keyCode_;
	};

	class ARTEM_ENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeadCount)
			: KeyEvent(keycode), repeatCount_(repeadCount) {}

		inline int GetRepeatCount() const { return repeatCount_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode_ << " (" << repeatCount_ << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int repeatCount_;
	};

	class ARTEM_ENGINE_API KeyReleasedEvent : public KeyEvent
	{
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}