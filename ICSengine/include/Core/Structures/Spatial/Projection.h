#pragma once

#include "Containers/Spatial/Vector.h"
#include "Containers/Spatial/Matrix.h"

class Projection {
public:
	ICS_API Projection(Vector<unsigned int, 2> screen);
	ICS_API Projection(unsigned int width, unsigned int height);

	ICS_API void PerspectiveProject();
	ICS_API void RebuildProjection(unsigned int width, unsigned int height);
	ICS_API inline Vector<float, 2> GetNearFar() { return { m_ZNear,m_ZFar }; }
	ICS_API inline Vector<float, 2> GetFovCharacteristics() { return { m_Fov,m_FovTrig }; }
	ICS_API inline Vector<float, 3> GetWindowCharacteristics() { return { m_Width,m_Height,m_AspectRatio }; }
	ICS_API inline Vector<float, 4> GetFrustrumSize() { return { m_FTop,m_FBottom,m_FRight,m_FLeft }; }
	ICS_API inline Matrix<float, 4>& GetProjection() { return m_Projection; }

private:
	float m_ZNear;
	float m_ZFar;

	float m_FBottom;
	float m_FTop;
	float m_FLeft;
	float m_FRight;

	float m_Fov;
	float m_FovTrig;

	float m_AspectRatio;
	float m_Width;
	float m_Height;

	Matrix<float, 4> m_Projection;
};