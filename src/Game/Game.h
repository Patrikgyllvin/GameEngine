#ifndef GAME_H
#define GAME_H

#include "../Engine/Entity Core/EntityManager.h"

#include "../Engine/Core Components/TransformComponent.h"
#include "../Engine/Core Components/MovementComponent.h"
#include "../Engine/Core Systems/MovementSystem.h"

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
