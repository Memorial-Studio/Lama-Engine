//
// Created by Jack Daniels on 06.12.2024.
//

#include "LECore/Window.h"
#include "LECore/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LamaEngine
{
    static bool s_GLFW_initialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		: m_title(std::move(title))
		, m_height(height)
		, m_width(width)
	{
		int resultCode = init();
	}
	Window::~Window()
	{
		shotdown();
	}
	int Window::init()
	{
        LOG_INFO("Creating window {0} with size {1}x{2}", m_title, m_width, m_height);
        if (!s_GLFW_initialized)
        {
            /* Initialize the library */
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialize GLFW!");
                return -1;
            }
            s_GLFW_initialized = true;
        }

        /* Create a windowed mode window and its OpenGL context */
        m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            LOG_CRITICAL("Can't create window!");
            glfwTerminate();
            return -2;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to init GLAD");
            return -3;
        }

        return 0;
	}

	void Window::shotdown()
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}

    void Window::on_update()
    {
        glClearColor(0.13, 0.13, 0.13, 1);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}