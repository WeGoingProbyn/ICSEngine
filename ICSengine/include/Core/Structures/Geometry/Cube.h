#pragma once

#include "Core/Structures/Geometry/Geometry.h"

class Cube : public Geometry
{
public:
	bool FindIndices() override;
	bool FindVertices() override;
};