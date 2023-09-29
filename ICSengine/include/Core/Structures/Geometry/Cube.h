#pragma once

#include "Core/Structures/Geometry/Geometry.h"

class Cube : public Geometry
{
public:
	ICS_API Cube();
	ICS_API ~Cube();

private:
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;
};