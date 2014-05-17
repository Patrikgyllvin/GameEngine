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
	Entity* e = entityManager->genEntity();
	static_cast< TransformComponent* >( entityManager->addComponent( e, new TransformComponent() ) )->setPosition( 1.0, 1.0, 0.0 );
	static_cast< MovementComponent* >( entityManager->addComponent( e, new MovementComponent() ) )->setVelocity( 0.0, 0.0, -0.2 );

	Entity* a = entityManager->genEntity();
	static_cast< TransformComponent* >( entityManager->addComponent( a, new TransformComponent() ) )->setPosition( 1.0, 1.0, 0.0 );
	static_cast< MovementComponent* >( entityManager->addComponent( a, new MovementComponent() ) )->setVelocity( 0.0, 0.0, -0.2 );
}

void Game::tick()
{
}

void Game::render()
{}
