#pragma once

#include "Core/Structures/Geometry/Geometry.h"

class Circle : public Geometry
{
public:
	ICS_API Circle();
	ICS_API ~Circle();

private:
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;
};