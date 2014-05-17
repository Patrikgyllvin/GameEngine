#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <cstdio>
#include <cstdlib>

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	class Window
	{
	public:
		Window();
		~Window();
	
		int createWindow( int width, int height, std::string text, bool fullscreen );
		void destroyWindow();

		bool getInitialized();

		void swapBuffers();
	
	private:
		int setupGL();

		void cleanup();

		GLFWwindow *window;
	
		bool isInitialized;

		int w, h;
	};
}

#endif
