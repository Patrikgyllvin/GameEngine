/*
 * Core.h
 *
 *  Created on: 17 maj 2014
 *      Author: Patrik Gyllvin
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>

#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Engine {
	class Core {
	public:
		Core();
		virtual ~Core();

		void createWindow( int w, int h, std::string text, bool resizable, bool fullscreen );
		void destroyWindow();
		
		void start();
		void stop();
		
		void run();
		
		void init();
		void update();
		void render();
		
		void setFramerate( double framerate );
		
		// Sets function pointers which will be called at init, update and render, respectively
		void setInitFunction( void (*initFunc)() );
		void setUpdateFunction( void (*updtFunc)() );
		void setRenderFunction( void (*rndrFunc)() );

	private:
		Window* window;
		
		bool isRunning;
		double frameTime;
		double framerate;
		
		// TODO: Figure out delta-time thingy...
		void (*initializationFunc)();
		void (*updateFunc)();
		void (*renderFunc)();
	};
}

#endif
