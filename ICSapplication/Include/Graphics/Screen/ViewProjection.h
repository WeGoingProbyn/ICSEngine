#pragma once

#include "Containers/array/darray.h"

#include "Core/Events/EventListener.h"
#include "Core/Structures/Spatial/Camera.h"
#include "Core/Structures/Spatial/Projection.h"
#include "Core/Structures/Spatial/Transformation.h"

class ViewProjection : public EventListener
{
public:
	ICS_API ViewProjection();

	inline Matrix<float, 4> Project(Transformation& transform) { return (transform.Transform() * CameraProjection()).Transpose(); }

	inline Matrix<float, 4> GetCamera() { return m_Camera.Translate(); }
	inline Matrix<float, 4>& GetProjection() { m_Projection.GetProjection(); }
	inline Matrix<float, 4> CameraProjection() { return m_Camera.Translate() * m_Projection.GetProjection(); }

	bool ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex) override;
private:
	Camera m_Camera;
	Projection m_Projection;
};