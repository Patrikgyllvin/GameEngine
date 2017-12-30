#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../include/Game/Game.h"
#else
#include "Game.h"
#endif

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
}

int x = -5; bool a = false;
b2BodyDef bDef;


void Game::init()
{
    entityManager->registerSystem( new PhysicsSystem() );
    entityManager->registerSystem( new Engine::MovementSystem() );
    entityManager->registerSystem( new CarSystem() );
    entityManager->registerRenderingSystem( new RenderSystem() );
    
    bDef.type = b2_dynamicBody;
    bDef.position = b2Vec2( 0, 4 );
    bDef.linearVelocity = b2Vec2( 0.02, 0 );
    bDef.angle = 0.0;

    //entityManager->genEntity().addComponent( new PhysicsBodyComponent( b2_staticBody, b2Vec2( -2.5, -3.7 ), b2Vec2( 0, 0 ), 3.14/20, 2, 0.01, 0x001, 0x0001, 1 ) );
    //entityManager->genEntity().addComponent( new PhysicsBodyComponent( b2_staticBody, b2Vec2( 2.5, -3.7 ), b2Vec2( 0, 0 ), -3.14/20, 2, 0.01, 0x001, 0x0001, 1 ) );
    
    entityManager->genEntity().addComponent( &( new Engine::TransformComponent() )->setPosition( 0.0, 0.0, 10.0 ) ).addComponent( new CameraComponent() );
    
    Engine::KeyBinding binding = Engine::KeyBinding( "Forward", GLFW_KEY_W, Engine::NO_INPUT, Engine::NO_INPUT );
    inputHandler->addKeyBinding( binding );
    
    entityManager->init();
}

void Game::tick()
{
    bDef.position = b2Vec2( x, 4 );
    entityManager->genEntity().addComponent( new CarComponent() ).addComponent( new PhysicsBodyComponent( bDef, 0.1, 0.1, 0x0001, 0x0001, 1 ));
    
    if( a )
        --x;
    else
        ++x;
    
    if( x == 5 )
        a = true;
    else if( x == -5 )
        a = false;
    
    entityManager->update();
    inputHandler->update();
}

void Game::render()
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    entityManager->render();
}
