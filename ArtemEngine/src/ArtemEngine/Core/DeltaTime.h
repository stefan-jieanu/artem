#pragma once

namespace ArtemEngine {

	class DeltaTime
	{
	public:
		DeltaTime(float time = 0.0f)
			: time_(time)
		{

		}

		operator float() const { return time_; }

		float GetSeconds() const { return time_; }
		float GetMilliseconds() const { return time_ * 1000.0f; }

		// TODO: Override +, - operator
	private:
		float time_;
	};

}