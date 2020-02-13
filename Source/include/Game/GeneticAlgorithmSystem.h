//
//  GeneticAlgorithmSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2018-02-28.
//  Copyright © 2018 Patrik Gyllvin. All rights reserved.
//

#ifndef GeneticAlgorithmSystem_h
#define GeneticAlgorithmSystem_h

#include "../Engine/CoreSystems/System.h"

#include "../Engine/EntityCore/Entity.h"

#include "PhysicsBodyComponent.h"
#include "CarComponent.h"
#include "RayCastComponent.h"

#include "../Engine/CoreComponents/TransformComponent.h"

#include "DNAComponent.h"
#include "NeuralNetworkComponent.h"

#include "../Engine/Input/InputHandler.h"

#include <vector>

#include <random>
#include <cmath>

#include <Box2D/Box2D.h>

class GeneticAlgorithmSystem : public Engine::System
{
public:
    GeneticAlgorithmSystem( int popSize, float mutationRate );
    ~GeneticAlgorithmSystem();

    virtual bool shouldProcessEntity( const Engine::Entity& entity );

protected:
    virtual void init( Engine::EntityManager& entityManager ); // Create initial population, random weights...

    virtual void preProcess();
    virtual void processEntity( Engine::Entity& entity );
    virtual void postProcess();

private:
    float calculateFitness( const float& f );

    int selectRandomRanked( const std::vector< float >& vec );
    int selectRandomWeighted( const std::vector< float >& vec );
    int selectRandomProb( const std::vector< float >& vec );

    float highestFitness, generation;
    Engine::Entity* bestFit;
    int bestFitPos;

    std::vector< Engine::Entity* > dead;

    int popSize;
    float mutationRate;

    double time;
    bool reset;
};

#endif
