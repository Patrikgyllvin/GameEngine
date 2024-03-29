#include "../../../include/Engine/Core/Window.h"

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

	int Window::createWindow( int width, int height, std::string text, bool resizable, bool fullscreen )
	{
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, 1 );
#endif
		glfwWindowHint( GLFW_SAMPLES, 4 );

		if( resizable )
			glfwWindowHint( GLFW_RESIZABLE, 1 );
		else
			glfwWindowHint( GLFW_RESIZABLE, 0 );

		if( fullscreen )
			window = glfwCreateWindow( width, height, text.c_str(), glfwGetPrimaryMonitor(), nullptr );
		else
			window = glfwCreateWindow( width, height, text.c_str(), nullptr, nullptr );

		if( !window )
		{
			fprintf( stderr, "Could not create window!\n" );

			cleanup();

			return -1;
		}

		glfwMakeContextCurrent( window );

        glfwGetFramebufferSize( window, &this->w, &this->h );

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

	int Window::setupGL()
	{
		glViewport( 0, 0, this->w, this->h );

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

	int Window::shouldClose()
	{
		return glfwWindowShouldClose( window );
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
