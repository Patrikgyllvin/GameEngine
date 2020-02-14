#ifndef GAME_H
#define GAME_H

#include "../Engine/EntityCore/EntityManager.h"

#include "../Engine/CoreComponents/TransformComponent.h"
#include "../Engine/CoreComponents/MovementComponent.h"
#include "../Engine/CoreSystems/MovementSystem.h"

#include "../Engine/Input/InputHandler.h"

#include "PhysicsSystem.h"
#include "RenderSystem.h"

#include "CameraComponent.h"

#include "CarComponent.h"
#include "CarSystem.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Box2D/Box2D.h>

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
    
    Engine::InputHandler* inputHandler;
};

#endif
