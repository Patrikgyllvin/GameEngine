#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "Component.h"

class MovementComponent : public Component
{
public:
	MovementComponent() : Component( COMPONENT_MOVEMENT ) {}
	virtual ~MovementComponent() {}

	MovementComponent* setVelocity( float x, float y, float z )
	{
		velX = x;
		velY = y;
		velZ = z;

		return this;
	}

	MovementComponent* setVelocityX( float x )
	{
		velX = x;

		return this;
	}

	MovementComponent* setVelocityY( float y )
	{
		velY = y;

		return this;
	}

	MovementComponent* setVelocityZ( float z )
	{
		velZ = z;

		return this;
	}

	float getVelocityX()
	{
		return this->velX;
	}

	float getVelocityY()
	{
		return this->velY;
	}

	float getVelocityZ()
	{
		return this->velZ;
	}

private:
	float velX, velY, velZ;
};

#endif