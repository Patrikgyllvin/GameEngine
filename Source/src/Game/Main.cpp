/*
 * Main.cpp
 *
 *  Created on: 18 maj 2014
 *      Author: Patrik Gyllvin
 */

#include <iostream>

#include "Engine/Core/Core.h"

int main( int argc, char** argv )
{
	Engine::Core* engine = new Engine::Core();

	engine->createWindow( 800, 600, "3D Game", false, false );
	
	engine->start();

	return 0;
}
