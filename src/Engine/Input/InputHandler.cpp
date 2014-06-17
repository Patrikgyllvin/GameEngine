#include "InputHandler.h"

namespace Engine
{
	std::vector<KeyBinding> InputHandler::keyBindings;
	std::vector<Axis> InputHandler::axes;
	
	bool InputHandler::joyButtonLast[ GLFW_JOYSTICK_LAST * JOYSTICK_BUTTONS ] = { false };
	bool InputHandler::joysticks[ GLFW_JOYSTICK_LAST ] = { false };

	bool InputHandler::keyboardLast[ GLFW_KEY_LAST ] = { false };
	bool InputHandler::mouseButtonLast[ GLFW_MOUSE_BUTTON_LAST ] = { false };

	double InputHandler::lastMouseX = 0.0;
	double InputHandler::lastMouseY = 0.0;

	InputHandler::InputHandler()
	{}

	InputHandler::~InputHandler()
	{}


	void InputHandler::update()
	{
		const unsigned char* pressed;
		int nButtons;

		for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
		{
			if( joysticks[ i ] )
			{
				pressed = glfwGetJoystickButtons( i, &nButtons );

				for( int j = 0; j < ( nButtons < JOYSTICK_BUTTONS ? nButtons : JOYSTICK_BUTTONS ); j++ )
				{
					joyButtonLast[ j ] = pressed[ j ];
				}
			}
		}

		for( int i = 0; i < GLFW_KEY_LAST; i++ )
		{
			keyboardLast[ i ] = glfwGetKey( glfwGetCurrentContext(), i );
		}

		for( int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++ )
		{
			mouseButtonLast[ i ] = glfwGetMouseButton( glfwGetCurrentContext(), i );
		}

		glfwGetCursorPos( glfwGetCurrentContext(), &lastMouseX, &lastMouseY );
	}
	
	void InputHandler::addKeyBinding( KeyBinding binding )
	{
		keyBindings.push_back( binding );
	}

	void InputHandler::addAxis( Axis axis )
	{
		axes.push_back( axis );
	}

	void InputHandler::refreshJoysticks()
	{
		for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
		{
			joysticks[ i ] = ( glfwJoystickPresent( i ) == GL_TRUE );
		}
	}

	bool InputHandler::getKey( int key )
	{
		// TODO: Joystick support
		return glfwGetKey( glfwGetCurrentContext(), key );
	}

	bool InputHandler::getKeyUp( int key )
	{
		// TODO: Joystick support and fix UP
		return ( glfwGetKey( glfwGetCurrentContext(), key ) == GLFW_RELEASE );
	}

	bool InputHandler::getKeyDown( int key )
	{
		// TODO: Joystick support and fix DOWN
		return ( glfwGetKey( glfwGetCurrentContext( ), key ) == GLFW_PRESS );
	}

	bool InputHandler::getButton( const std::string& butName )
	{
		int button = GLFW_KEY_UNKNOWN, mouseButton = GLFW_KEY_UNKNOWN, joyButton = GLFW_KEY_UNKNOWN;
		bool pressed = false;

		for( KeyBinding bind : keyBindings )
		{
			if( bind.getName() == butName )
			{
				button = bind.getButton();
				joyButton = bind.getJoystickButton();
				mouseButton = bind.getMouseButton();

				break;
			}
			else
			{
				if( keyBindings.back().getName() == bind.getName() )
				{
					fprintf( stdout, "No such key bind: %s\n", butName.c_str() );
					return false;
				}
			}
		}

		bool kbdButDown = false, mouseButDown = false, joyButDown[ GLFW_JOYSTICK_LAST ] = { false };

		if( button != GLFW_KEY_UNKNOWN )
			kbdButDown = glfwGetKey( glfwGetCurrentContext(), button );
		if( mouseButton != GLFW_KEY_UNKNOWN )
			mouseButDown = glfwGetMouseButton( glfwGetCurrentContext(), mouseButton );
		if( joyButton != GLFW_KEY_UNKNOWN )
		{
			const unsigned char* pressed;

			for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
			{
				if( joysticks[ i ] )
				{
					int nButtons;

					pressed = glfwGetJoystickButtons( i, &nButtons );

					joyButDown[ i ] = pressed[ joyButton ];
				}
			}
		}

		for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
		{
			pressed = ( pressed || joyButDown[ i ] );
		}

		return ( kbdButDown || mouseButDown || pressed );
	}

	bool InputHandler::getButtonUp( const std::string& butName )
	{
		int button = GLFW_KEY_UNKNOWN, mouseButton = GLFW_KEY_UNKNOWN, joyButton = GLFW_KEY_UNKNOWN;
		bool released = false;

		for( KeyBinding bind : keyBindings )
		{
			if( bind.getName( ) == butName )
			{
				button = bind.getButton( );
				joyButton = bind.getJoystickButton( );
				mouseButton = bind.getMouseButton( );

				break;
			}
			else
			{
				if( keyBindings.back().getName() == bind.getName() )
				{
					fprintf( stdout, "No such key bind: %s\n", butName.c_str() );
					return false;
				}
			}
		}

		bool kbdButUp = false, mouseButUp = false, joyButUp[ GLFW_JOYSTICK_LAST ] = { false };

		if( button != GLFW_KEY_UNKNOWN )
			if( keyboardLast[ button ] )
				kbdButUp = ( glfwGetKey( glfwGetCurrentContext( ), button ) == GLFW_RELEASE );
		if( mouseButton != GLFW_KEY_UNKNOWN )
			if( mouseButtonLast[ mouseButton ] )
				mouseButUp = ( glfwGetMouseButton( glfwGetCurrentContext( ), mouseButton ) == GLFW_RELEASE );
		if( joyButton != GLFW_KEY_UNKNOWN )
		{
			const unsigned char* pressed;

			for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
			{
				if( joysticks[ i ] )
				{
					int nButtons;

					pressed = glfwGetJoystickButtons( i, &nButtons );

					if( joyButtonLast[ joyButton ] && !pressed[ joyButton ] )
					{
						joyButUp[ i ] = true;
					}
				}
			}
		}

		for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
		{
			released = ( released || joyButUp[ i ] );
		}

		
		return ( kbdButUp || mouseButUp || released );
	}
	
	bool InputHandler::getButtonDown( const std::string& butName )
	{
		int button = GLFW_KEY_UNKNOWN, mouseButton = GLFW_KEY_UNKNOWN, joyButton = GLFW_KEY_UNKNOWN;
		bool down = false;

		for( KeyBinding bind : keyBindings )
		{
			if( bind.getName( ) == butName )
			{
				button = bind.getButton( );
				joyButton = bind.getJoystickButton( );
				mouseButton = bind.getMouseButton( );

				break;
			}
			else
			{
				if( keyBindings.back( ).getName( ) == bind.getName( ) )
				{
					fprintf( stdout, "No such key bind: %s\n", butName.c_str( ) );
					return false;
				}
			}
		}

		bool kbdButUp = false, mouseButUp = false, joyButUp[ GLFW_JOYSTICK_LAST ] = { false };

		if( button != GLFW_KEY_UNKNOWN )
			if( !keyboardLast[ button ] )
				kbdButUp = ( glfwGetKey( glfwGetCurrentContext( ), button ) == GLFW_PRESS );
		if( mouseButton != GLFW_KEY_UNKNOWN )
			if( !mouseButtonLast[ mouseButton ] )
				mouseButUp = ( glfwGetMouseButton( glfwGetCurrentContext( ), mouseButton ) == GLFW_PRESS );
		if( joyButton != GLFW_KEY_UNKNOWN )
		{
			const unsigned char* pressed;

			for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
			{
				if( joysticks[ i ] )
				{
					int nButtons;

					pressed = glfwGetJoystickButtons( i, &nButtons );

					if( !joyButtonLast[ joyButton ] && pressed[ joyButton ] )
					{
						joyButUp[ i ] = true;
					}
				}
			}
		}

		for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
		{
			down = ( down || joyButUp[ i ] );
		}


		return ( kbdButUp || mouseButUp || down );
	}

	float InputHandler::getAxis( const std::string& axisName )
	{
		int keyPositive = GLFW_KEY_UNKNOWN, keyNegative = GLFW_KEY_UNKNOWN, mouseAxis = GLFW_KEY_UNKNOWN, joyAxis = GLFW_KEY_UNKNOWN;

		for( Axis axis : axes )
		{
			if( axis.getName() == axisName )
			{
				keyPositive = axis.getKeyPositive();
				keyNegative = axis.getKeyNegative();

				mouseAxis = axis.getMouseAxis();

				joyAxis = axis.getJoystickAxis();

				break;
			}
			else
			{
				if( axis.getName() == axes.back().getName() )
				{
					fprintf( stdout, "No such axis: %s\n", axisName.c_str() );
					return 0;
				}
			}
		}

		float keyboard = 0.0f, mouse = 0.0f, joystick[ GLFW_JOYSTICK_LAST ] = { 0.0f };

		if( keyPositive != GLFW_KEY_UNKNOWN )
		{
			if( getKey( keyPositive ) )
				keyboard = 1;
		}
		if( keyNegative != GLFW_KEY_UNKNOWN )
		{
			if( getKey( keyNegative ) )
				keyboard = -1;
		}

		if( mouseAxis != NO_INPUT )
		{
			double mouseX, mouseY;
			glfwGetCursorPos( glfwGetCurrentContext(), &mouseX, &mouseY );

			if( mouseAxis == MOUSE_AXIS_X )
				mouse = mouseX - lastMouseX;
			else if( mouseAxis == MOUSE_AXIS_Y )
				mouse = mouseY - lastMouseY;
		}
		
		if( joyAxis != NO_INPUT )
		{
			const float* axis;
			int nAxes;

			for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
			{
				if( joysticks[ i ] )
				{
					axis = glfwGetJoystickAxes( i, &nAxes );
/* ADSASD
					float a = axis[ 0 ], fractPt, intPt;
					fractPt = modf( a, &intPt );

					fractPt *= 10;
					fractPt = (int)fractPt / 10.0;

					a = intPt + fractPt;

					joystick[ i ] = a;*/
				}
			}
		}

		float joystickAxisMoved = 0.0f;

		for( int i = 0; i < GLFW_JOYSTICK_LAST; i++ )
		{
			if( joystick[ i ] > 0.101 || joystick[ i ] < -0.101 )
			{
				joystickAxisMoved = joystick[ i ];
			}
		}

		if( joystickAxisMoved )
			return joystickAxisMoved;

		if( mouse )
			return mouse;

		if( keyboard )
			return keyboard;
	}

	void InputHandler::getMousePos( double* mouseX, double* mouseY )
	{
		glfwGetCursorPos( glfwGetCurrentContext(), mouseX, mouseY );
	}

	bool InputHandler::getMouseButton( int mouseButton )
	{
		return glfwGetMouseButton( glfwGetCurrentContext(), mouseButton );
	}
}
