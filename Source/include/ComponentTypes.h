#ifndef COMPONENTTYPES_H
#define COMPONENTTYPES_H

enum ComponentType {
	COMPONENT_TRANSFORM = 0,
	COMPONENT_MOVEMENT,
	COMPONENT_SPRITE,
	COMPONENT_ANIMATION,
    
	COMPONENT_LAST
};

const unsigned int COMPONENT_TRANSFORM_BIT = 1 << COMPONENT_TRANSFORM;
const unsigned int COMPONENT_MOVEMENT_BIT = 1 << COMPONENT_MOVEMENT;
const unsigned int COMPONENT_SPRITE_BIT = 1 << COMPONENT_SPRITE;
const unsigned int COMPONENT_ANIMATION_BIT = 1 << COMPONENT_ANIMATION;

#endif
