#ifndef GAME_H
#define GAME_H

#include "../Engine/EntityCore/EntityManager.h"

#include "../Engine/CoreComponents/TransformComponent.h"
#include "../Engine/CoreComponents/MovementComponent.h"
#include "../Engine/CoreSystems/MovementSystem.h"

class Game
{
public:
	Game();
	~Game();

	void init();

	void tick();
	void render();

private:
	Engine::EventManager* eventManager;
	Engine::EntityManager* entityManager;
};

#endif
