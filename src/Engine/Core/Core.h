/*
 * Core.h
 *
 *  Created on: 17 maj 2014
 *      Author: Patrik Gyllvin
 */

#ifndef CORE_H
#define CORE_H

#include <iostream>

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
		
		// Sets function pointers which will be called at init, update and render, respectively
		void setInitFunction( void (*initFunc)() );
		void setUpdateFunction( void (*updtFunc)() );
		void setRenderFunction( void (*rndrFunc)() );

	private:
		Window* window;
		
		// TODO: Figure out delta-time thingy...
		void (*initializationFunc)();
		void (*updateFunc)();
		void (*renderFunc)();
	};
}

#endif
