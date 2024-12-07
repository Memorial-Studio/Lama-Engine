//
// Created by Ganza on 05.12.2024.
// Looked by ____ on XX.XX.20XX.
// Changed by Jack Daniels on 06.12.2024
// Approved and improved by _____ on XX.XX.20XX
//

#include <iostream>
#include <memory>
#include <LECore/Application.h>

class LEApp : public LamaEngine::Application 
{
	virtual void on_update() override
	{
		//std::cout << "Update frame: " << frame++ << std::endl;
	}

	int frame = 0;
};

int main()
{
	auto leApp = std::make_unique<LEApp>();

	int returnCode = leApp->start(1280, 720, "LEngine"); 

	std::cin.get();

	return returnCode;
}