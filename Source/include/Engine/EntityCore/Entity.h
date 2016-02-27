#ifndef ENTITY_H
#define ENTITY_H

#include "../CoreComponents/Component.h"

#include "EntityManager.h"

namespace Engine
{
    typedef std::vector< std::vector< Component* > > ComponentList;
	
	class Entity
	{
		friend class EntityManager;
		
	public:
        EntityManager& entityManager;
		
		~Entity()
		{
			destroyAllComponents();

			for (unsigned int i = 0; i < COMPONENT_LAST; i++)
				components[i].clear();

			components.clear();
		}

		const EntityID getID() const { return id; }

		const unsigned int getTypeBits() const { return typeBits; }

		bool hasComponent( unsigned int componentBit ) const
		{
			return ( typeBits & componentBit ) == componentBit;
		}

		void addComponent( Component* comp )
		{
			std::vector< Component* >& compList = components[ comp->getType() ];

			compList.push_back( comp );

			typeBits |= comp->getTypeBits();

			// Notify systems
			//eventManager->pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_ADDED, entity ) );
		}

		Component& getFirstComponentOf( ComponentType compType ) const
		{
			return *( components[ compType ] )[ 0 ];
		}

		std::vector< Component* >& getComponents( ComponentType compType )
		{
			std::vector< Component* >& compList = components[ compType ];

			// No components of type compType...
			if( !compList.size() )
			{
                // TODO: Fix this shit!
				//return EMPTY?;
			}

			return compList;
		}

		void destroyAllComponents()
		{
			for( unsigned int i = 0; i < COMPONENT_LAST; i++ )
			{
				if( components[ i ].empty() )
					continue;

				destroyFirstComponent( (ComponentType)i );
			}
		}

		void destroyFirstComponent( ComponentType compType )
		{
			std::vector< Component* >& compList = components[ compType ];

			if( compList.empty() )
				return;

			if( compList[ 0 ] != nullptr )
			{
				delete compList[ 0 ];
				compList[ 0 ] = nullptr;
			}

			// No more components of type
			if( compList[ 0 ] == nullptr && compList.empty() )
				this->typeBits &= ( ~compType );

			// Notify systems
			//TODO: eventManager !?
            //eventManager->pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_DESTROYED, entity ) );
		}

		void destroyEntity()
		{
			destroyAllComponents();

			entityManager.destroyEntity( this );
		}

	private:
        Entity( EntityID eID, EntityManager& eMgr ) : id( eID ), entityManager( eMgr )
		{
			components.resize( COMPONENT_LAST );
		}

		const EntityID id;

		unsigned int typeBits;

		ComponentList components;
	};
}

#endif