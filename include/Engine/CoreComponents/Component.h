#ifndef COMPONENT_H
#define COMPONENT_H

#include "ComponentTypes.h"

namespace Engine
{
	class Component
	{
	public:
		Component( ComponentType compType ) : type( compType ), typeBits( 1 << compType ) {}
		virtual ~Component() {}

		ComponentType getType() const { return type; }
		const unsigned int getTypeBits() const { return typeBits; }

	private:
		ComponentType type;
		unsigned int typeBits;
	};
}

#endif
