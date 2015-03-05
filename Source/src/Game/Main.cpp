/*
 * Main.cpp
 *
 *  Created on: 18 maj 2014
 *      Author: Patrik Gyllvin
 */

#include <iostream>

#ifndef __APPLE__
#include "Engine/Core/Core.h"
#else
#include "Core.h"
#endif

int main( int argc, char** argv )
{
	Engine::Core* engine = new Engine::Core();

	engine->createWindow( 800, 600, "3D Game", false, false );
	
	engine->start();

	return 0;
}