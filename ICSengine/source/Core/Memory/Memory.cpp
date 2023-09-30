#include "Core/Memory/Memory.h"
#include "Core/Debugger/Logger.h"

// TODO: Remove no?
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdarg.h>

// These seem better off as static parts so that the
// memory manipulation functions can be called statically
// throughout the engine...

Memory::Memory()
{
	// TODO: Initialise a large block of memory on module load and disperse to
	//		application when it is requested, sounds a lot quicker than setting up memory all the time
	m_Initialised = true;
	ICS_INFO("Memory: Initialising memory module...")
}


Memory::~Memory()
{
	// TODO: More in depth breakdown of where hanging allocation is
	// NOTE: Application holds pointers to object which need to be
	// NOTE: constructed and destructed at certain times. There will
	// NOTE: always be at least as many pointers live as objects within application
	m_Initialised = false;
}
