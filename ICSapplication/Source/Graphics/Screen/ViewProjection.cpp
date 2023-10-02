#include "Graphics/Screen/ViewProjection.h"
#include "Application/Config.h"

ViewProjection::ViewProjection()
	:
	m_Projection({ Config::platform.width, Config::platform.height })
{
	m_Projection.PerspectiveProject();
}