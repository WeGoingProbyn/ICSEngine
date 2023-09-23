#include "Layers/LayerManager.h"

#include <Core/Debugger/Logger.h>
#include <Core/Memory/MemoryTypes.h>

LayerManager::LayerManager()
	:
	m_LayerStack(MemoryType::ICS_RENDERER)
{
}

LayerManager::~LayerManager()
{
	if (m_LayerStack.Size() > 0)
	{
		ICS_WARN("LayerManager: There are still live layers on layer stack, Layers must be deleted by user at shutdown")
	}
}
