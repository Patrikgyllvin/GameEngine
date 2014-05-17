#ifndef GAME_H
#define GAME_H

#include "EntityManager.h"

#include "Core Components/TransformComponent.h"
#include "Core Components/MovementComponent.h"
#include "Core Systems/MovementSystem.h"

class Game
{
public:
	Game();
	~Game();

	void init();

	void tick();
	void render();

private:
	EventManager* eventManager;
	EntityManager* entityManager;
	System* moveSys;
};

#endif
