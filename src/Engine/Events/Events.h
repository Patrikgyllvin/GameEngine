#ifndef EVENTS_H
#define EVENTS_H

enum EventType
{
	EVENT_ENTITY_CREATED = 0,
	EVENT_ENTITY_DESTROYED,
	EVENT_ENTITY_COMPONENT_ADDED,
	EVENT_ENTITY_COMPONENT_DESTROYED,

	EVENT_LAST
};

class IEvent
{
public:
	IEvent( EventType eType ) : type( eType ) {}
	virtual ~IEvent() {}

	EventType getType() const { return type; }

private:
	EventType type;
};

class IEventListener
{
public:
	virtual ~IEventListener() {}
	
	virtual void processEvent( const IEvent& e ) = 0;
};

#endif