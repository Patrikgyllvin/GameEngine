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
	window( new Window() ),
	initializationFunc( nullptr ),
	updateFunc( nullptr ),
	renderFunc( nullptr )
	{
		glfwInit();
	}

	Core::~Core()
	{
		delete window;
		glfwTerminate();
	}

	void Core::createWindow(int w, int h, std::string text, bool resizable, bool fullscreen )
	{
		if( window->getInitialized() )
		{
			std::cout << "Warning: Cannot create more than one window!\n";
			return;
		}

		window->createWindow( w, h, text, resizable, fullscreen );
	}

	void Core::destroyWindow()
	{
		if( window->getInitialized() )
			window->destroyWindow();
		else
			std::cout << "Warning: Cannot destroy non-existent window!\n";
	}
	
	void Core::setInitFunction( void (*initFunc)() )
	{
		initializationFunc = initFunc;
	}
	
	void Core::setUpdateFunction( void (*updtFunc)() )
	{
		updateFunc = updtFunc;
	}
	
	void Core::setRenderFunction( void (*rndrFunc) () )
	{
		renderFunc = rndrFunc;
	}
}
