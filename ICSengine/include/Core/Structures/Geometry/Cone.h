#pragma once

#include "Core/Structures/Geometry/Circle.h"


class Cone : public Circle
{
	friend class Arrow;
public:
	ICS_API Cone();
	ICS_API ~Cone();
	ICS_API Cone(unsigned int faces);
	ICS_API Cone(unsigned int faces, bool build_buffers);

private:
	ICS_API void Build(bool build_buffers);
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;
};