/*
 * Core.cpp
 *
 *  Created on: 17 maj 2014
 *      Author: Patrik Gyllvin
 */

#include "Core.h"

namespace Engine {
	Core::Core()
	:
	window( new Window() )
	{
	}

	Core::~Core()
	{
		delete window;
	}

	void Core::createWindow(int w, int h, std::string text, bool fullscreen )
	{
		if( window->getInitialized() )
		{
			std::cout << "Warning: Cannot create more than one window!\n";
			return;
		}

		window->createWindow( w, h, text, fullscreen );
	}

	void Core::destroyWindow()
	{
		if( window->getInitialized() )
			window->destroyWindow();
		else
			std::cout << "Warning: Cannot destroy non-existent window!\n";
	}
}
