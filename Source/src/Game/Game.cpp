#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../include/Game/Game.h"
#else
#include "Game.h"
#endif

Game::Game()
:
eventManager( new Engine::EventManager() ),
entityManager( new Engine::EntityManager( eventManager ) )
{}

Game::~Game()
{
	delete entityManager;
	delete eventManager;
}

void Game::init()
{
    entityManager->registerSystem( new Engine::MovementSystem() );
    
    entityManager->genEntity().addComponent( &( new Engine::TransformComponent() )->setPosition( 1.0, 1.0, 1.0 ) )
        .addComponent( new Engine::MovementComponent() );
}

void Game::tick()
{
    entityManager->update();
}

void Game::render()
{
    glClear( GL_COLOR_BUFFER_BIT );
}
