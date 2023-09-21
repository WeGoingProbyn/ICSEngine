#pragma once

#include "Core/Geometry/Geometry.h"

class Cube : public Geometry
{
public:
	bool FindIndices() override;
	bool FindVertices() override;
};