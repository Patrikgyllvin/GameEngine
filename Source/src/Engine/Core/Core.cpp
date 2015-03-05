/*
 * Core.cpp
 *
 *  Created on: 17 maj 2014
 *      Author: Patrik Gyllvin
 */

#ifndef __APPLE__
#include "Engine/Core/Core.h"
#else
#include "Core.h"
#endif

void errorCallback( int error, const char* desc )
{
	fputs( desc, stderr );
	std::cout << "\n";
}

namespace Engine {
	Core::Core()
	:
	window( new Window() ),
	isRunning( false ),
	framerate( 10000.0 ),
	frameTime( 1.0 / framerate ),
	initializationFunc( nullptr ),
	updateFunc( nullptr ),
	renderFunc( nullptr )
	{
		glfwInit();

		glfwSetErrorCallback( errorCallback );
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
	
	void Core::start()
	{
		if( isRunning )
		{
			std::cout << "Cannot start; already running!\n";
			return;
		}
		
		run();
	}
	
	void Core::stop()
	{
		if( !isRunning )
		{
			std::cout << "Cannot stop; not running!\n";
			return;
		}
		
		isRunning = false;
	}
	
	void Core::run()
	{
		init();
		
		isRunning = true;
		
		double lastTime = glfwGetTime();
		double currTime = lastTime;
		double deltaTime = 0;
		
		double unproccessedTime = 0;
		
		double frameCounter = 0;
		int frames;
		
		while( isRunning )
		{
			bool willRender;
			
			frameTime = 1.0 / framerate;
			
			currTime = glfwGetTime();
			deltaTime = currTime - lastTime;
			lastTime = currTime;
			
			unproccessedTime += deltaTime;
			
			frameCounter += deltaTime;
			
			if( frameCounter >= 1.0 )
			{
				std::cout << "FPS: " << frames << '\n';
				frames = 0;
				frameCounter = 0;
			}
			
			while( unproccessedTime > frameTime )
			{
				willRender = true;
				
				if( window->shouldClose() )
					stop();
				
				update();
				
				unproccessedTime -= frameTime;
			}
			
			if( willRender )
			{
				render();
				
				frames++;
			}
			else
			{
				std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
			}
		}
	}
	
	void Core::init()
	{
		// Add INIT shit here
		
		
		if( initializationFunc )
			initializationFunc();
	}
	
	void Core::update()
	{
		// Add update shit here
		
		
		if( updateFunc )
			updateFunc();

		glfwPollEvents();
	}
	
	void Core::render()
	{
		// Add render shit here
		
		if( renderFunc )
			renderFunc();

		window->swapBuffers();
	}
	
	void Core::setFramerate( double framerate )
	{
		this->framerate = framerate;
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
