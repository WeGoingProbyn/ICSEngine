#pragma once

#include "Core/Events/EventHandler.h"

//NOTE: This may seem weird but it stops some precarious header loops
//NOTE:	this would at first glance seem better in Platform.h but 
//NOTE:	EventHandler needs to include types such as narray and darray
//NOTE:	these types depend on ICS memory subsytems, as memory needs
//NOTE:	to include platform.h to access ICS memory functions this will cause a header loop

class EventOwner
{
public:
	EventOwner();
	virtual ~EventOwner() {}

	inline EventHandler& GetEventHandler() { return m_EventHandler; }
protected:
	EventHandler m_EventHandler;
};