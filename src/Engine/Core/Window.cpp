#include "Window.h"

namespace Engine
{
	Window::Window()
	:
	window( nullptr ),
	isInitialized( false ),
	w( 0 ),
	h( 0 )
	{}

	Window::~Window()
	{
		cleanup();
	}

	int Window::createWindow( int width, int height, std::string text, bool fullscreen )
	{
		// TODO: fullscreen support

		window = glfwCreateWindow( width, height, text.c_str(), nullptr, nullptr );

		if( !window )
		{
			fprintf( stderr, "Could not create window!\n" );

			cleanup();

			return -1;
		}

		glfwMakeContextCurrent( window );

		glfwGetWindowSize( window, &this->w, &this->h );

		GLenum err = glewInit();
		if( err != GLEW_OK )
		{
			fprintf( stderr, "Could not initialize GLEW, %s\n", glewGetErrorString( err ) );

			cleanup();

			return -1;
		}

		if( setupGL() != 0 )
		{
			cleanup();

			return -1;
		}

		isInitialized = true;

		return 0;
	}

	void Window::destroyWindow()
	{
		glfwDestroyWindow( window );
	}

	bool Window::getInitialized()
	{
		return isInitialized;
	}

	int Window::setupGL()
	{
		glViewport( 0, 0, this->w, this->h );

		return 0;
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers( window );
	}

	void Window::cleanup()
	{
		destroyWindow();
	}
}
