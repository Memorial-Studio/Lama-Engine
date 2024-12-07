//
// Created by Jack Daniels on 05.12.2024.
// 

#pragma once
#include <string>

struct GLFWwindow;

namespace LamaEngine
{
	class Window
	{
	public:
		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		void on_update();

		unsigned int get_width() const { return m_width; }
		unsigned int get_height() const { return m_height; }

	private:
		int init();
		void shotdown();

		GLFWwindow* m_pWindow;

		std::string m_title;
		unsigned int m_width, m_height;

	};
}