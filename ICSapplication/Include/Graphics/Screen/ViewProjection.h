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
	ICS_API ~ViewProjection() {}

	inline Matrix<float, 4> Project(Transformation& transform, Camera& camera, Projection& projection) 
	{ 
		return (transform.Transform() * CameraProjection(camera, projection)).Transpose();
	}
	inline Matrix<float, 4> Project(Matrix<float, 4>& transform, Camera& camera, Projection& projection) 
	{ 
		return (transform * CameraProjection(camera, projection)).Transpose();
	}

	inline Camera& GetCameraObj() { return m_Camera; }
	inline Projection& GetProjectionObj() { return m_Projection; }
	inline Matrix<float, 4> GetCamera() { return m_Camera.Translate(); }
	inline Matrix<float, 4> GetProjection() { m_Projection.GetProjection(); }
	inline Matrix<float, 4> CameraProjection(Camera& camera, Projection& projection) 
	{ 
		return camera.Translate() * projection.GetProjection();
	}

	void OnStartUp();
private:
	bool ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex) override;
private:
	Camera m_Camera;
	Projection m_Projection;
};