#include "../../include/Game/GeneticAlgorithmSystem.h"

GeneticAlgorithmSystem::GeneticAlgorithmSystem( int popSize, float mutationRate )
:
highestFitness( 0.0 ),
generation( 1.0 ),
bestFit( nullptr ),
bestFitPos( 0 ),
popSize( popSize ),
mutationRate( mutationRate ),
time( 0.0 ),
reset( true )
{
    dead.reserve( popSize );
}

GeneticAlgorithmSystem::~GeneticAlgorithmSystem()
{}

bool GeneticAlgorithmSystem::shouldProcessEntity( const Engine::Entity& entity )
{
    return entity.hasComponent( COMPONENT_NEURAL_NETWORK_BIT | COMPONENT_PHYSICS_BIT | COMPONENT_DNA_BIT | COMPONENT_CAR_BIT ) ||
        entity.hasComponent( COMPONENT_CAMERA_BIT | COMPONENT_TRANSFORM_BIT );
}

// Create initial population, random weights...
void GeneticAlgorithmSystem::init( Engine::EntityManager& entityManager )
{
    b2BodyDef bDef;
    bDef.type = b2_dynamicBody;
    bDef.position = b2Vec2( 0, 0 );
    bDef.linearVelocity = b2Vec2( 0, 0 );
    bDef.angle = 0.0;

    for( int i = 0; i != popSize; ++i )
    {
        std::vector< float > genome;
        genome.reserve( 37 );

        for( int i = 0; i != 37; ++i )
        {
            genome.push_back( 1000.0 * ( ( (double)rand() / RAND_MAX ) * 2 - 1 ) );
        }

        entityManager.genEntity().addComponent( new PhysicsBodyComponent( bDef, 1, 2, 0x0001, 0x0002, 1 ) ).addComponent( new CarComponent( true ) ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new NeuralNetworkComponent( genome ) ).addComponent( new DNAComponent( genome, -1, -1 ) );

        // Use to copy DNA
        /*std::vector< float > dna = {-848.316, 438.574, -729.617, 880.067, -359.025, 102.226, 120.158, 731.212, -680.815, -567.266, -648.133, -239.796, -344.675, 281.145, 547.626, 801.405, -939.167, -317.389, 7.23181, -117.707, -374.451, -400.157, 591.463, 720.007, 118.265, 831.396, 891.142, 868.241, -784.94, 311.236, 663.003, 99.6272, -894.181, 752.205, 407.302, -461.633, 712.185};
        entityManager.genEntity().addComponent( new PhysicsBodyComponent( bDef, 1, 2, 0x0001, 0x0002, 1 ) ).addComponent( new CarComponent( true ) ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new NeuralNetworkComponent( dna ) ).addComponent( new DNAComponent( dna, -1, -1 ) );*/
    }
}

void GeneticAlgorithmSystem::preProcess()
{
    // Do evolution algorithm
    if( dead.size() == popSize )
    {
        reset = false;

        // Start new population
        // Selection
        std::vector< float > matingPool( dead.size(), 0 );
        DNAComponent* dnaComp = nullptr;

        std::cout << "Generation: " << generation << '\n';
        std::cout << "Individ\tFitness\tGenom\tF1\tF2\n";

        for( int i = 0; i != dead.size(); ++i )
        {
            dnaComp = &static_cast< DNAComponent& >( dead[ i ]->getFirstComponentOf( COMPONENT_DNA ) );

            matingPool[ i ] = dnaComp->getFitness();

            std::cout << i << '\t' << dnaComp->getFitness() << '\t';

            for( auto &f : dnaComp->getGenome() )
            {
                std::cout << f << ' ';
            }

            std::cout << '\t' << dnaComp->getParent1() << '\t' << dnaComp->getParent2() << '\n';
        }

        // Reproduction
        Engine::Entity* parent1 = nullptr, *parent2 = nullptr;
        DNAComponent* parent1DNA = nullptr, *parent2DNA = nullptr;
        int p1, p2;

        for( int i = 0; i != popSize - 1; ++i )
        {
            p1 = selectRandomRanked( matingPool );
            p2 = selectRandomRanked( matingPool );

            parent1 = dead[ p1 ];
            parent2 = dead[ p2 ];

            parent1DNA = &static_cast< DNAComponent& >( parent1->getFirstComponentOf( COMPONENT_DNA ) );
            parent2DNA = &static_cast< DNAComponent& >( parent2->getFirstComponentOf( COMPONENT_DNA ) );

            const std::vector<float >& parent1Genome( parent1DNA->getGenome() ), &parent2Genome( parent2DNA->getGenome() );
            std::vector< float > childGenome( parent1Genome.size(), 0.0 );

            std::random_device rd;
            std::mt19937 gen( rd() );
            std::bernoulli_distribution mutate( mutationRate );
            std::bernoulli_distribution parent2( 0.5 );
            std::uniform_int_distribution<> dist( 0, parent1Genome.size() - 2 );
            int singlePoint = dist( gen );

            // Crossover & mutation
            for( int j = 0; j != parent1Genome.size(); ++j )
            {
                // Should gene be mutated?
                if( mutate( gen ) )
                {
                    childGenome[ j ] = 1000.0 * ( ( (double)rand() / RAND_MAX ) * 2 - 1 );
                }
/*
                // Median crossover
                else
                {
                    childGenome[ j ] = ( parent1Genome[ j ] + parent2Genome[ j ] ) / 2.0;
                }*/

                // Uniform crossover

                else if( parent2( gen ) ) // Does gene come from parent 2?
                {
                    childGenome[ j ] = parent2Genome[ j ];
                }
                else // Parent 1
                {
                    childGenome[ j ] = parent1Genome[ j ];
                }
/*
                // Single-point crossover
                else if( j > singlePoint )
                {
                    childGenome[ j ] = parent2Genome[ j ];
                }
                else
                {
                    childGenome[ j ] = parent1Genome[ j ];
                }*/
            }

            // Create child with new genome
            b2BodyDef bDef;
            bDef.type = b2_dynamicBody;
            bDef.position = b2Vec2( 0, 0 );
            bDef.linearVelocity = b2Vec2( 0, 0 );
            bDef.angle = 0.0;

            parent1->entityManager.genEntity().addComponent( new PhysicsBodyComponent( bDef, 1, 2, 0x0001, 0x0002, 1 ) ).addComponent( new CarComponent( true ) ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new NeuralNetworkComponent( childGenome ) ).addComponent( new DNAComponent( childGenome, p1, p2 ) );
        }

        DNAComponent& bestFitDNA = static_cast< DNAComponent& >( bestFit->getFirstComponentOf( COMPONENT_DNA ) );

        b2BodyDef bDef;
        bDef.type = b2_dynamicBody;
        bDef.position = b2Vec2( 0, 0 );
        bDef.linearVelocity = b2Vec2( 0, 0 );
        bDef.angle = 0.0;
        bestFit->entityManager.genEntity().addComponent( new PhysicsBodyComponent( bDef, 1, 2, 0x0001, 0x0002, 1 ) ).addComponent( new CarComponent( true ) ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new RayCastComponent() ).addComponent( new NeuralNetworkComponent( bestFitDNA.getGenome() ) ).addComponent( new DNAComponent( bestFitDNA.getGenome(), bestFitPos, -1 ) );

        // Kill off old generation
        for( auto it = dead.begin(); it != dead.end(); ++it )
        {
            (*it)->destroyEntity();
        }
        dead.clear();

        bestFit = nullptr;
        highestFitness = 0.0;

        // Reset time
        time = 0.0;
        ++generation;
    }

    time += 1 / 100.0;
}

void GeneticAlgorithmSystem::processEntity( Engine::Entity& entity )
{
    if( entity.hasComponent( COMPONENT_CAMERA_BIT ) )
    {
        if( !bestFit )
            return;

        Engine::TransformComponent& transComp = static_cast< Engine::TransformComponent& >( entity.getFirstComponentOf( COMPONENT_TRANSFORM ) );
        PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( bestFit->getFirstComponentOf( COMPONENT_PHYSICS ) );

        const b2Vec2& pos = physComp.getBody()->GetPosition();

        transComp.setPosition( pos.x, pos.y, transComp.getPosZ() );

        return;
    }

    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );
    CarComponent& carComp = static_cast< CarComponent& >( entity.getFirstComponentOf( COMPONENT_CAR ) );
    DNAComponent& dnaComp = static_cast< DNAComponent& >( entity.getFirstComponentOf( COMPONENT_DNA ) );

    if( !physComp.isAlive() && !dnaComp.isDead() )
    {
        dead.push_back( &entity );
        dnaComp.setDead( true );

        if( bestFit == &entity )
        {
            bestFitPos = dead.size() - 1;
        }
    }
    else if( !dnaComp.isDead() )
    {
        // Calculate fitness
        dnaComp.setFitness( calculateFitness( carComp.getDistance() ) );

        if( dnaComp.getFitness() > highestFitness )
        {
            highestFitness = dnaComp.getFitness();
            bestFit = &entity;
        }
/*
        std::cout << "Generation: " << generation << '\t';
        std::cout << "Distance: " << carComp.getDistance() << '\t';
        std::cout << "Fitness: " << dnaComp.getFitness() << '\n';*/
    }

    // Taking too long, kill all, go to next generation
    if( Engine::InputHandler::getButton( "Reset" ) && reset )
    {
        physComp.setAlive( false );
    }

    if( Engine::InputHandler::getButtonUp( "Reset" ) && dead.size() != popSize )
    {
        reset = true;
    }
}

void GeneticAlgorithmSystem::postProcess()
{}

float GeneticAlgorithmSystem::calculateFitness( const float& f )
{
    /*
    if( f > 0 )
        return pow( f, 4.0 ) / time;
    else
        return -pow( f, 4.0 ) / time;
     */

    return f;
}

int GeneticAlgorithmSystem::selectRandomRanked( const std::vector< float >& vec )
{
    std::vector< float > tmp( vec );
    std::sort( tmp.begin(), tmp.end() );

    std::vector< float > prob;

    float sum = 0.0;
    for( int i = 1; i != popSize + 1; ++i )
    {
        sum += i;
    }

    for( int i = 0; i != tmp.size(); ++i )
    {
        prob.push_back( ( i + 1 ) / sum );
    }

    auto rit = std::find( vec.rbegin(), vec.rend(), tmp[ selectRandomProb( prob ) ] );

    return std::distance( vec.begin(), rit.base() ) - 1;
}

int GeneticAlgorithmSystem::selectRandomWeighted( const std::vector< float >& vec )
{
    float sum = 0.0;
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        sum += *it;
    }

    std::vector< float > tmp;
    tmp.reserve( vec.size() );
    for( int i = 0; i != vec.size(); ++i )
    {
        tmp.push_back( (float)vec[ i ] / (float)sum );
    }

    return selectRandomProb( tmp );
}

int GeneticAlgorithmSystem::selectRandomProb( const std::vector< float >& vec )
{
    int index = 0;

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_real_distribution< float > dist( 0.0, std::nextafter( 1.0, DBL_MAX ) );

    float r = dist( gen );

    while( r > 0.0 )
    {
        r -= vec[ index ];
        index++;
    }

    return index - 1;
}
