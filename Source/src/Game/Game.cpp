#include "../../include/Game/Game.h"

Game::Game()
:
eventManager( new Engine::EventManager() ),
entityManager( new Engine::EntityManager( eventManager ) ),
inputHandler( new Engine::InputHandler() )
{}

Game::~Game()
{
	delete entityManager;
	delete eventManager;
    delete inputHandler;
}

void Game::init()
{}

void Game::tick()
{
    entityManager->update();
    inputHandler->update();
}

void Game::render()
{
    glClear( GL_COLOR_BUFFER_BIT );

    entityManager->render();
}
