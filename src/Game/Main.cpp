/*
 * Main.cpp
 *
 *  Created on: 18 maj 2014
 *      Author: Patrik Gyllvin
 */

#include <iostream>

#include "../Engine/Core/Core.h"

int main( int argc, char** argv )
{
	Engine::Core* engine = new Engine::Core();

	engine->createWindow( 600, 800, "3D Game", false );

	return 0;
}
