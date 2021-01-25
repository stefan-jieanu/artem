#include "aepch.h"

#include "Application.h"
#include "glad/glad.h"
#include "Input.h"

namespace ArtemEngine
{
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::sInstance_ = nullptr;

	Application::Application()
	{
		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		sInstance_ = this;

		LOG_CORE_TRACE("engine");
		LOG_CORE_DEBUG("engine");
		LOG_CORE_INFO("engine");
		LOG_CORE_WARN("engine");
		LOG_CORE_ERROR("engine");
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running_)
		{
			for (std::shared_ptr<Layer> layer : layerStack_)
				layer->OnUpdate();

			window_->OnUpdate();
		}
	}

	void Application::Terminate()
	{
		running_ = false;
	}

	void Application::PushLayer(std::shared_ptr<Layer> layer)
	{
		layerStack_.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(std::shared_ptr<Layer> layer)
	{
		layerStack_.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));
		dispatcher.Dispatch<KeyRepeatEvent>(BIND_EVENT_FN(Application::OnKeyRepeat));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(Application::OnKeyReleased));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(Application::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(Application::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Application::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Application::OnMouseScrolled));

		// If the event was not marked as handled by any of the previous callbacks
		// then send the event to the layers
		if (!e.IsHandled())
			for (std::shared_ptr<Layer> layer : layerStack_)
			{
				layer->OnEvent(e);
				if (e.IsHandled())
					break;
			}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		return false;
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}
	
	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		return false;
	}
	
	bool Application::OnKeyRepeat(KeyRepeatEvent& e)
	{
		return false;
	}
	
	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		return false;
	}
	
	bool Application::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}
	
	bool Application::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		return false;
	}
	
	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{
		return false;
	}
	
	bool Application::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}
}