#pragma once

#include "Core/Structures/Geometry/Geometry.h"

class Circle : public Geometry
{
public:
	ICS_API Circle();
	virtual ICS_API ~Circle();
	ICS_API Circle(unsigned int faces);

protected:
	ICS_API Circle(unsigned int face, bool build_buffer);
	ICS_API Circle(unsigned int face, float base_origin_depth, bool build_buffer);
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;

	ICS_API void Build(float base_origin_depth, bool build_buffer);

protected:
	unsigned int m_Faces;
};