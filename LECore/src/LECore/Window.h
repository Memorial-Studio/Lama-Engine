//
// Created by Jack Daniels on 05.12.2024.
// 
// Changed by Jack Daniels on 07.12.2024.
// 

#pragma once
#include <string>
#include "LECore/Event.h"
#include <functional>

struct GLFWwindow;

namespace LamaEngine
{
	class Window
	{
	public:
		using EventCallBackFn = std::function<void(BaseEvent&)>;

		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		void on_update();

		unsigned int get_width() const { return m_data.width; }
		unsigned int get_height() const { return m_data.height; }

		void set_event_callback(const EventCallBackFn callback)
		{
			m_data.eventCallbackFn = callback;
		}

	private:
		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			EventCallBackFn eventCallbackFn;
		};

		int init();
		void shotdown();

		GLFWwindow* m_pWindow = nullptr;
		WindowData m_data;
		float m_background_color[4] = { 0.15f, 0.15f, 0.15f, 0.f };
	};
}