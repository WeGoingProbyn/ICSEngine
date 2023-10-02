#include "Core/Structures/Spatial/Projection.h"

Projection::Projection(unsigned int width, unsigned int height)
{
	RebuildProjection(width, height);
}

Projection::Projection(Vector<unsigned int, 2> screen) 
	:	
	Projection(screen[0], screen[1])
{
}

void Projection::RebuildProjection(unsigned int width, unsigned int height)
{
	m_Projection = Matrix<float, 4>();
	m_ZFar = 100.0f;
	m_ZNear = 0.1f;

	m_Fov = 45 * (3.14159f / 180.0f); // Hard coded to 45 degree
	m_FovTrig = std::tan(0.5f * m_Fov);

	m_Width = (float)width;
	m_Height = (float)height;
	m_AspectRatio = (float)width / (float)height;

	m_FTop = m_FovTrig * m_ZNear;
	m_FBottom = -m_FTop;
	m_FRight = m_FTop * m_AspectRatio;
	m_FLeft = -m_FRight;
}

void Projection::PerspectiveProject() 
{
	m_Projection = Matrix<float, 4>();
	m_Projection(0, 0) = 2 * m_ZNear / (m_FTop - m_FBottom);
	m_Projection(1, 1) = 2 * m_ZNear / (m_FRight - m_FLeft);

	m_Projection(2, 2) = -(m_ZFar + m_ZNear) / (m_ZFar - m_ZNear);
	m_Projection(3, 2) = -2 * m_ZFar * m_ZNear / (m_ZFar - m_ZNear);

	m_Projection(2, 3) = -1;

	m_Projection(0, 2) = (m_FRight + m_FLeft) / (m_FRight - m_FLeft);
	m_Projection(1, 2) = (m_FTop + m_FBottom) / (m_FTop - m_FBottom);
}

//void Projection::OrthographicProject() {
//	m_Projection = Matrix<float, 4>(true, 1);
//	m_Projection(0, 0) = m_Width * 0.5f;
//	m_Projection(1, 1) = m_Height * 0.5f;
//	m_Projection(2, 2) = 1.0f / (m_ZFar - m_ZNear);
//	m_Projection(3, 2) = -(1.0f / (m_ZFar - m_ZNear)) * m_ZNear;
//}
