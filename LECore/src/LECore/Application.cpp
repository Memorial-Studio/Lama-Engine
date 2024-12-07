//
// Created by Ganza on 05.12.2024.
// 
// Changed by Jack Daniels on 05.12.2024.
//

#include "LECore/Application.h"
#include "LECore/Log.h"
#include "LECore/Window.h"
#include <iostream>

namespace LamaEngine
{
	Application::Application() 
	{
        LOG_INFO("Starting application...");

	}

	Application::~Application() 
	{
		LOG_INFO("Closing application...");
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char* title) 
	{
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);

		while (true) 
		{
			m_pWindow->on_update();
			on_update();
		}

        return 0;
	}
}