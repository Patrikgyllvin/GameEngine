#include "Game.h"

Game::Game()
:
eventManager( new Engine::EventManager() ),
entityManager( new Engine::EntityManager( eventManager ) ),
moveSys( new Engine::MovementSystem( eventManager, entityManager ) )
{}

Game::~Game()
{
	delete entityManager;
	delete eventManager;
}

void Game::init()
{
	Engine::Entity* e = entityManager->genEntity();
	static_cast< Engine::TransformComponent* >( entityManager->addComponent( e, new Engine::TransformComponent() ) )->setPosition( 1.0, 1.0, 0.0 );
	static_cast< Engine::MovementComponent* >( entityManager->addComponent( e, new Engine::MovementComponent() ) )->setVelocity( 0.0, 0.0, -0.2 );

	Engine::Entity* a = entityManager->genEntity();
	static_cast< Engine::TransformComponent* >( entityManager->addComponent( a, new Engine::TransformComponent() ) )->setPosition( 1.0, 1.0, 0.0 );
	static_cast< Engine::MovementComponent* >( entityManager->addComponent( a, new Engine::MovementComponent() ) )->setVelocity( 0.0, 0.0, -0.2 );
}

void Game::tick()
{
}

void Game::render()
{}
