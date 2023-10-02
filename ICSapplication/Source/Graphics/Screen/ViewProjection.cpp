#include "Graphics/Screen/ViewProjection.h"
#include "Application/Config.h"

ViewProjection::ViewProjection()
	:
	m_Projection(Config::platform.width, Config::platform.height)
{
	m_Projection.PerspectiveProject();
}

bool ViewProjection::ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex)
{
	switch (EventIndex)
	{
	case static_cast<char>(EventListener::EventTypes::ICS_PLATFORM_STATE_CHANGE):
		m_Projection.RebuildProjection(Config::platform.width, Config::platform.width);
		return true;
	}
	return false;
}
