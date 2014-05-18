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
	isRunning( false ),
	frameTime( 1.0 / 10000.0 ),
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
	
	void start()
	{
		if( isRunning )
		{
			std::cout << "Cannot start; already running!\n";
			return;
		}
		
		run();
	}
	
	void stop()
	{
		if( !isRunning )
		{
			std::cout << "Cannot stop; not running!\n";
			return;
		}
		
		isRunning = false;
	}
	
	void run()
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
			bool render;
			
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
				render = true;
				
				if( window->shouldClose() )
					stop();
				
				update();
				
				unproccessedTime -= frameTime;
			}
			
			if( render )
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
	
	void init()
	{
		// Add INIT shit here
		
		
		if( initializationFunc )
			initializationFunc();
	}
	
	void update()
	{
		// Add update shit here
		
		
		if( updateFunc )
			updateFunc();
	}
	
	void render()
	{
		// Add render shit here
		
		
		if( renderFunc )
			renderFunc();
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
