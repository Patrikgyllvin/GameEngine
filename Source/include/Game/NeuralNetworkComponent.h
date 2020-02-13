#ifndef NeuralNetworkComponent_h
#define NeuralNetworkComponent_h

#include "../Engine/CoreComponents/Component.h"

#include <Eigen/Eigen>

#include <iostream>

class NeuralNetworkComponent : public Engine::Component
{
public:
    NeuralNetworkComponent()
    :
    Component( COMPONENT_NEURAL_NETWORK )
    {
        hiddenWeights = 100 * hiddenWeights.setRandom();
        outputWeights = 100 * outputWeights.setRandom();

        hiddenBias = 100 * hiddenBias.setRandom();
        outputBias = 100 * outputBias.setRandom();
    }

    NeuralNetworkComponent( const std::vector< float >& genome )
    :
    Component( COMPONENT_NEURAL_NETWORK )
    {
        hiddenWeights.setZero();
        outputWeights.setZero();

        hiddenBias.setZero();
        outputBias.setZero();

        setWeightsFromGenome( genome );
    }

    ~NeuralNetworkComponent()
    {
    }

    // Set all weights and biases according to genome
    void setWeightsFromGenome( const std::vector< float >& genome )
    {
        // Hidden Weights
        for( int i = 0; i != hiddenWeights.size(); ++i )
        {
            hiddenWeights( i ) = genome[ i ];
        }

        // Output Weights
        for( int i = 0; i != outputWeights.size(); ++i )
        {
            outputWeights( i ) = genome[ i + hiddenWeights.size() ];
        }

        // Hidden Biases
        for( int i = 0; i != hiddenBias.size(); ++i )
        {
            hiddenBias( i ) = genome[ i + hiddenWeights.size() + outputWeights.size() ];
        }

        // Output Biases
        for( int i = 0; i != outputBias.size(); ++i )
        {
            outputBias( i ) = genome[ i + hiddenWeights.size() + outputWeights.size() + hiddenBias.size() ];
        }
    }
/*
    void setHiddenWeights( const Eigen::Matrix< float, 3, 4 >& weights )
    {
        this->hiddenWeights = weights;
    }

    void setOutputWeights( const Eigen::Matrix< float, 2, 3 >& weights )
    {
        this->outputWeights = weights;
    }

    void setHiddenBias( const Eigen::Matrix< float, 3, 1 >& bias )
    {
        this->hiddenBias = bias;
    }

    void setOutputBias( const Eigen::Matrix< float, 2, 1 >& bias )
    {
        this->outputBias = bias;
    }
*/
    const Eigen::Vector2f feedForward( const Eigen::Vector4f& input )
    {
        // Feed-forward algorithm
        // Hidden layer
        Eigen::Matrix< float, 5, 1 > hidden = ( hiddenWeights * input ) + hiddenBias;
        // Activation
        for( int i = 0; i != hidden.rows(); ++i )
        {
            for( int j = 0; j != hidden.cols(); ++j )
            {
                hidden( i, j ) = activationFunction( hidden( i, j ) );
            }
        }

        // Output layer
        Eigen::Matrix< float, 2, 1 > output = ( outputWeights * hidden ) + outputBias;
        // Activation
        for( int i = 0; i != output.rows(); ++i )
        {
            for( int j = 0; j != output.cols(); ++j )
            {
                output( i, j ) = activationFunction( output( i, j ) );
            }
        }

        return output;
    }

    float activationFunction( float x )
    {
        //return ( 2.0 / ( 1 + exp( -x ) ) ) - 1.0; // logistic sigmoid, moved down
        return tanh( x );
    }

private:
    Eigen::Matrix< float, 5, 4 > hiddenWeights;
    Eigen::Matrix< float, 2, 5 > outputWeights;

    Eigen::Matrix< float, 5, 1 > hiddenBias;
    Eigen::Matrix< float, 2, 1 > outputBias;
};

#endif
