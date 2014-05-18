#ifndef ENTITY_H
#define ENTITY_H

typedef unsigned int EntityID;

namespace Engine
{
	class Entity
	{
		friend class EntityManager;

	public:
		~Entity() {}

		EntityID getID() const { return id; }

		unsigned int getTypeBits() const { return typeBits; }

	private:
		Entity( EntityID eID ) : id( eID ), typeBits( 0 ) {}

		const EntityID id;

		unsigned int typeBits;
	};
}

#endif
