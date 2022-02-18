/*
 * Main.cpp
 *
 *  Created on: 18 maj 2014
 *      Author: Patrik Gyllvin
 */

#include <iostream>
#include <memory>

#include "Engine/Core/Core.h"
#include "Game/Game.h"

std::unique_ptr< Game > game;

void init()
{
    game->init();
}

void render()
{
    game->render();
}

void update()
{
    game->tick();
}

int main( int argc, char** argv )
{
	Engine::Core engine{};
    game = std::make_unique< Game >();

    engine.setRenderFunction(&render);
    engine.setUpdateFunction(&update);
    engine.setInitFunction(&init);

	engine.createWindow( 800, 600, "3D Game", false, false );

	engine.start();

	return 0;
}
