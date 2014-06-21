#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include <iostream>

namespace Engine
{
#define NO_INPUT -1

#define JOYSTICK_BUTTON_1 0
#define JOYSTICK_BUTTON_2 1
#define JOYSTICK_BUTTON_3 2
#define JOYSTICK_BUTTON_4 3
#define JOYSTICK_BUTTON_5 4
#define JOYSTICK_BUTTON_6 5
#define JOYSTICK_BUTTON_7 6
#define JOYSTICK_BUTTON_8 7
#define JOYSTICK_BUTTON_9 8
#define JOYSTICK_BUTTON_10 9
#define JOYSTICK_BUTTON_11 10
#define JOYSTICK_BUTTON_12 11
#define JOYSTICK_BUTTON_13 12
#define JOYSTICK_BUTTON_14 13
#define JOYSTICK_BUTTON_15 14
#define JOYSTICK_BUTTON_16 15
#define JOYSTICK_BUTTON_17 16
#define JOYSTICK_BUTTON_18 17
#define JOYSTICK_BUTTON_19 18
#define JOYSTICK_BUTTON_20 19
#define JOYSTICK_BUTTONS 20

#define MOUSE_AXIS_X 0
#define MOUSE_AXIS_Y 1

#define JOYSTICK_AXIS_1 0
#define JOYSTICK_AXIS_2 1
#define JOYSTICK_AXIS_3 2
#define JOYSTICK_AXIS_4 3
#define JOYSTICK_AXIS_5 4
#define JOYSTICK_AXIS_6 5
#define JOYSTICK_AXIS_7 6
#define JOYSTICK_AXIS_8 7
#define JOYSTICK_AXIS_9 8
#define JOYSTICK_AXIS_10 9

	typedef struct KeyBinding
	{
		KeyBinding( const std::string& name, int key, int mouseBut, int joyBut )
		:
		name( name ),
		key( key ),
		mouseBut( mouseBut ),
		joyBut( joyBut )
		{}

		void changeKey( int key )
		{
			this->key = key;
		}

		void changeMouseBut( int key )
		{
			this->key = key;
		}

		void changeJoyBut( int joyBut )
		{
			this->joyBut = joyBut;
		}

		const std::string& getName( )
		{
			return this->name;
		}

		int getButton( )
		{
			return this->key;
		}

		int getMouseButton( )
		{
			return this->mouseBut;
		}

		int getJoystickButton( )
		{
			return this->joyBut;
		}

	private:
		std::string name;
		int key, mouseBut, joyBut;

	} KeyBinding;

	typedef struct Axis
	{
		Axis( const std::string& name, int keyPos, int keyNeg, int mouseAxis, int joyAxis )
		:
		name( name ),
		keyPos( keyPos ),
		keyNeg( keyNeg ),
		mouseAxis( mouseAxis ),
		joyAxis( joyAxis )
		{}

		void changeKeyPositive( int keyPos )
		{
			this->keyPos = keyPos;
		}

		void changeKeyNegative( int keyNeg )
		{
			this->keyNeg = keyNeg;
		}

		void changeMouseAxis( int mouseAxis )
		{
			this->mouseAxis = mouseAxis;
		}
		
		void changeJoyAxis( int joyAxis )
		{
			this->joyAxis = joyAxis;
		}

		const std::string& getName()
		{
			return this->name;
		}

		int getKeyPositive()
		{
			return this->keyPos;
		}
		
		int getKeyNegative()
		{
			return this->keyNeg;
		}

		int getMouseAxis()
		{
			return this->mouseAxis;
		}

		int getJoystickAxis()
		{
			return this->joyAxis;
		}

	private:
		std::string name;
		int keyPos, keyNeg, mouseAxis, joyAxis;
	} Axis;

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void update();

		void addKeyBinding( KeyBinding binding );
		void addAxis( Axis axis );

// TODO: change keybinding & axis
// Change functions to check name !exist

		static void refreshJoysticks();

		static bool getKey( int key );
		static bool getKeyUp( int key );
		static bool getKeyDown( int key );
		
		static bool getButton( const std::string& butName );
		static bool getButtonUp( const std::string& butName );
		static bool getButtonDown( const std::string& butName );

		static float getAxis( const std::string& axisName );

		static void getMousePos( double* mouseX, double* mouseY );
		static bool getMouseButton( int mouseButton );

	private:
		static std::vector<KeyBinding> keyBindings;
		static std::vector<Axis> axes;

		static bool joyButtonLast[ GLFW_JOYSTICK_LAST * JOYSTICK_BUTTONS ];
		static bool joysticks[ GLFW_JOYSTICK_LAST ];

		static bool keyboardLast[ GLFW_KEY_LAST ];
		static bool mouseButtonLast[ GLFW_MOUSE_BUTTON_LAST ];

		static double lastMouseX, lastMouseY;
	};
}

#endif
