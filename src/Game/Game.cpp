#include "Game/Game.h"

Game::Game()
:
entityManager{},
inputHandler{}
{}

Game::~Game()
{}

void Game::init()
{}

void Game::tick()
{
    entityManager.update();
    inputHandler.update();
}

void Game::render()
{
    glClear( GL_COLOR_BUFFER_BIT );

    entityManager.render();
}
