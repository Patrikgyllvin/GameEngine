#include "Game.h"

Game::Game()
:
eventManager( new EventManager() ),
entityManager( new EntityManager( eventManager ) ),
moveSys( new MovementSystem( eventManager, entityManager ) )
{}

Game::~Game()
{
	delete entityManager;
	delete eventManager;
}

void Game::init()
{
}

void Game::tick()
{
}

void Game::render()
{}
