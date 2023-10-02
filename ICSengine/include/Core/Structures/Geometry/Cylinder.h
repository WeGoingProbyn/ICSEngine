#pragma once

#include "Core/Structures/Geometry/Circle.h"

class Cylinder : public Circle
{
	friend class Arrow;
public:
	ICS_API Cylinder();
	ICS_API ~Cylinder();
	ICS_API Cylinder(unsigned int faces);
	ICS_API Cylinder(unsigned int faces, bool build_buffers);

	ICS_API void Build(unsigned int faces, bool build_buffers);

private:
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;
};
