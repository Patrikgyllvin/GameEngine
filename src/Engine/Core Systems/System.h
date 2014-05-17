#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>

#include "../Events/EventManager.h"
#include "../Entity Core/EntityManager.h"

class System : public IEventListener
{
public:
	System( EventManager* evtManager, EntityManager* entManager, unsigned int compTypeBits );
	virtual ~System();

	virtual void processEvent( const IEvent& e );

	void update();

protected:

	virtual void init() = 0;

	virtual void preUpdate() = 0;

	virtual void updateEntities( const std::set< Entity* >& entities ) = 0;

	virtual void postUpdate() = 0;

	EntityManager* entityManager;
	EventManager* eventManager;

private:
	std::set< Entity* > chosenOnes;

	unsigned int typeBits;
};

#endif
