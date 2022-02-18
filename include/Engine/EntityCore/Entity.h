#ifndef ENTITY_H
#define ENTITY_H

#include "../CoreComponents/Component.h"

#include "EntityManager.h"

namespace Engine
{
    typedef std::vector< std::vector< Component* > > ComponentList;
    typedef unsigned int EntityID;

	class Entity
	{
		friend class EntityManager;

	public:
        EntityManager& entityManager;

		~Entity()
		{
			destroyAllComponents();
		}

		const EntityID getID() const { return id; }

		const unsigned int getTypeBits() const { return typeBits; }

		bool hasComponent( unsigned int componentBit ) const
		{
			return ( typeBits & componentBit ) == componentBit;
		}

		Entity& addComponent( Component* comp )
		{
			std::vector< Component* >& compList = components[ comp->getType() ];

			compList.push_back( comp );

            typeBits |= comp->getTypeBits();

			// Notify systems
			eventManager.pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_ADDED, this, comp ) );

            return *this;
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
				return empty;
			}

			return compList;
		}

		void destroyAllComponents()
		{
			for( unsigned int i = 0; i != COMPONENT_LAST; i++ )
			{
				if( components[ i ].empty() )
					continue;

                for( auto it = components[ i ].begin(); it != components[ i ].end(); ++it )
                {
                    destroyComponent( *it );
                }
                components[ i ].clear();
			}

            components.clear();
		}

        // Change to take ID or component
		void destroyLastComponent( ComponentType compType )
		{
			std::vector< Component* >& compList = components[ compType ];

            // Notify systems
            eventManager.pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_DESTROYED, this, &compList.back() ) );

			if( compList.empty() )
				return;

            delete compList[ compList.size() - 1 ];
			compList.pop_back();

			// No more components of type
			if( compList.empty() )
				this->typeBits &= ( ~compType );
		}

        void destroyComponent( Component* component )
        {
            std::vector< Component* >& compList = components[ component->getType() ];

            // Notify systems
            eventManager.pushEvent( EntityEvent( EVENT_ENTITY_COMPONENT_DESTROYED, this, component ) );

            if( compList.empty() )
                return;

            if( component != nullptr )
            {
                delete component;
                component = nullptr;
            }

            // No more components of type
            if( component == nullptr && compList.empty() )
                this->typeBits &= ( ~component->getType() );
        }

		void destroyEntity()
		{
			entityManager.destroyEntity( this );
		}

	private:
        Entity( EntityID eID, EntityManager& eMgr, const EventManager& evtMgr ) : entityManager( eMgr ), eventManager( evtMgr ), id( eID ), typeBits( 0 )
		{
			components.resize( COMPONENT_LAST );
            empty.push_back(nullptr);
		}

        const EventManager& eventManager;

		const EntityID id;

		unsigned int typeBits;

		ComponentList components;

        std::vector< Component* > empty;
	};
}

#endif
