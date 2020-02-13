#include "../../include/Game/Game.h"

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

Engine::Entity* cam, *car;

void Game::init()
{
	srand( (unsigned int) time( 0 ) );

    entityManager->registerSystem( new PhysicsSystem( b2Vec2( 0, 0 ), *eventManager ) );
    entityManager->registerSystem( new Engine::MovementSystem() );
    entityManager->registerSystem( new CarSystem( *eventManager ) );
    entityManager->registerSystem( new RayCastSystem( *eventManager ) );
	entityManager->registerSystem( new GeneticAlgorithmSystem( 40, 0.04 ) );

    entityManager->registerRenderingSystem( new RenderSystem() );

#if !defined __APPLE__ || defined _MAC_MAKEFILE
    Texture* t = new Texture( "Res/Tex/Track1.png" );
#else
    Texture* t = new Texture( "Track.png" );
#endif

    Track* track = new Track( *t, *entityManager );
    track->makeCurrent();

    cam = &entityManager->genEntity().addComponent( &( new Engine::TransformComponent() )->setPosition( 0.0, 0.0, 100.0 ) ).addComponent( new CameraComponent() );
	//car = &entityManager->genEntity().addComponent( &( new CarComponent() ))

    b2BodyDef bDef;
    bDef.type = b2_dynamicBody;
    bDef.position = b2Vec2( 0, 0 );
    bDef.linearVelocity = b2Vec2( 0, 0 );
    bDef.angle = 0.0;
    //car = &entityManager->genEntity().addComponent( new PhysicsBodyComponent( bDef, 1, 2, 0x0001, 0x0002, 1 ) ).addComponent( new CarComponent( false ) ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() );

    Engine::KeyBinding fwd = Engine::KeyBinding( "Forward", GLFW_KEY_W, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding bwd = Engine::KeyBinding( "Backward", GLFW_KEY_S, Engine::NO_INPUT, Engine::NO_INPUT );

    Engine::KeyBinding right = Engine::KeyBinding( "Turn right", GLFW_KEY_D, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding left = Engine::KeyBinding( "Turn left", GLFW_KEY_A, Engine::NO_INPUT, Engine::NO_INPUT );

    Engine::KeyBinding zoomOut = Engine::KeyBinding( "Zoom out", GLFW_KEY_SEMICOLON, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding zoomIn = Engine::KeyBinding( "Zoom in", GLFW_KEY_MINUS, Engine::NO_INPUT, Engine::NO_INPUT );

    Engine::KeyBinding reset = Engine::KeyBinding( "Reset", GLFW_KEY_R, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding space = Engine::KeyBinding( "Space", GLFW_KEY_SPACE, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding one = Engine::KeyBinding( "1", GLFW_KEY_1, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding two = Engine::KeyBinding( "2", GLFW_KEY_2, Engine::NO_INPUT, Engine::NO_INPUT );
    Engine::KeyBinding three = Engine::KeyBinding( "3", GLFW_KEY_3, Engine::NO_INPUT, Engine::NO_INPUT );

    inputHandler->addKeyBinding( fwd );
    inputHandler->addKeyBinding( bwd );
    inputHandler->addKeyBinding( right );
    inputHandler->addKeyBinding( left );

    inputHandler->addKeyBinding( zoomIn );
    inputHandler->addKeyBinding( zoomOut );

    inputHandler->addKeyBinding( reset );
    inputHandler->addKeyBinding( space );

    inputHandler->addKeyBinding( one );
    inputHandler->addKeyBinding( two );
    inputHandler->addKeyBinding( three );

    entityManager->init();
}

void Game::tick()
{
    entityManager->update();
    inputHandler->update();

    /*
    Engine::TransformComponent& transComp = static_cast< Engine::TransformComponent& >( cam->getFirstComponentOf( COMPONENT_TRANSFORM ) );
    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( car->getFirstComponentOf( COMPONENT_PHYSICS ) );
    const b2Vec2& pos = physComp.getBody()->GetPosition();

    transComp.setPosition( pos.x, pos.y, transComp.getPosZ() );*/

    if( Engine::InputHandler::getButton( "Zoom in" ) )
    {
        Engine::TransformComponent& camTrans = static_cast< Engine::TransformComponent& >( cam->getFirstComponentOf( COMPONENT_TRANSFORM ) );
        camTrans.setPosZ( camTrans.getPosZ() - 1 );
    }

    if( Engine::InputHandler::getButton( "Zoom out" ) )
    {
        Engine::TransformComponent& camTrans = static_cast< Engine::TransformComponent& >( cam->getFirstComponentOf( COMPONENT_TRANSFORM ) );
        camTrans.setPosZ( camTrans.getPosZ() + 1 );
    }
    /*
    if( Engine::InputHandler::getButton( "Reset" ) )
    {
        car->destroyEntity();

        b2BodyDef bDef;
        bDef.type = b2_dynamicBody;
        bDef.position = b2Vec2( 0, 0 );
        bDef.linearVelocity = b2Vec2( 0, 0 );
        bDef.angle = 0.0;
        car = &entityManager->genEntity().addComponent( new PhysicsBodyComponent( bDef, 1, 2, 0x0001, 0x0002, 1 ) ).addComponent( new CarComponent( false ) ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() );
    }*/
}

void Game::render()
{
    glClear( GL_COLOR_BUFFER_BIT );

    entityManager->render();
}
