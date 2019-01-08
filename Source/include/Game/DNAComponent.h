#ifndef DNAComponent_h
#define DNAComponent_h

#include "../Engine/CoreComponents/Component.h"

#include <vector>

class DNAComponent : public Engine::Component
{
public:
    DNAComponent( const std::vector< float >& genome, int p1, int p2 )
    :
    Component( COMPONENT_DNA ),
    fitness( 0.0 ),
    dead( false ),
    p1( p1 ),
    p2( p2 ),
    genome( genome )
    {}

    DNAComponent()
    :
    Component( COMPONENT_DNA ),
    fitness( 0.0 ),
    dead( false ),
    p1( -1 ),
    p2( -1 ),
    genome()
    {
        genome.reserve( 100 );

        for( int i = 0; i != 100; ++i )
        {
            genome.push_back( 100 * ( ( (double)rand() / RAND_MAX ) * 2 - 1 ) );
        }
    }

    ~DNAComponent()
    {}

    void setFitness( const float& fitness )
    {
        this->fitness = fitness;
    }

    const float& getFitness() const
    {
        return this->fitness;
    }

    void setDead( bool dead )
    {
        this->dead = dead;
    }

    const bool& isDead() const
    {
        return this->dead;
    }

    void setParent1( int p1 )
    {
        this->p1 = p1;
    }

    const int getParent1() const
    {
        return this->p1;
    }

    void setParent2( int p2 )
    {
        this->p2 = p2;
    }

    const int getParent2() const
    {
        return this->p2;
    }

    void setGenome( const std::vector< float >& genome )
    {
        this->genome = genome;
    }

    const std::vector< float >& getGenome() const
    {
        return this->genome;
    }

private:
    float fitness;
    bool dead;

    int p1, p2;

    std::vector< float > genome;
};

#endif
