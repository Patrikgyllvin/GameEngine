#ifndef ENTITY_H
#define ENTITY_H

#include "EntityManager.h"

#include "../CoreComponents/Component.h"

typedef unsigned int EntityID;

namespace Engine
{
	typedef std::vector< std::vector< std::vector< Component* > > > ComponentList;

	class Entity
	{
		friend class EntityManager;
		
	public:
		~Entity() {}

		EntityID getID() const { return id; }

		unsigned int getTypeBits() const { return typeBits; }

		bool hasComponent( unsigned int componentBit ) const
		{
			return ( typeBits & componentBit ) == componentBit;
		}

		//void addComponent();

		Component& getFirstComponent( ComponentType compType ) const
		{
			return *( ( components[ compType ] )[ this->id ] )[ 0 ];
		}

		std::vector< Component* >& getComponents( ComponentType compType ) const
		{
			std::vector< std::vector< Component* > >& entList = components[ compType ];

			// Entity not in list - doesn't contain any components of type compType...
			if(this->id >= entList.size() )
			{
				return;
			}

			return entList[ this->id ];
		}

		void destroyAllComponents()
		{
			for( unsigned int i = 0; i < COMPONENT_LAST; i++ )
			{
				std::vector< std::vector< Component* > >& entList = components[ i ];

				if( this->id >= entList.size() )
					break;

				destroyFirstComponent( (ComponentType)i );
			}
		}

		void destroyFirstComponent( ComponentType compType )
		{
			std::vector< std::vector< Component* > >& entList = components[ compType ];

			if( this->id >= entList.size() )
				return;

			std::vector< Component* >& entCompList = entList[ this->id ];

			if( entCompList[ 0 ] != nullptr )
			{
				delete entCompList[ 0 ];
				entCompList[ 0 ] = nullptr;
			}

			// No more components of type
			if( entCompList[ 0 ] == nullptr && entCompList.empty() )
				this->typeBits &= ( ~compType );

			// Notify systems
			eventManager->pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_DESTROYED, entity ) );
		}

	private:
		Entity( EntityID eID, EntityManager& eMgr, ComponentList& comps ) : id( eID ), entityManager( eMgr ), components( comps ) {}

		EntityManager& entityManager;

		const EntityID id;

		unsigned int typeBits;

		ComponentList& components;
	};
}

#endif
