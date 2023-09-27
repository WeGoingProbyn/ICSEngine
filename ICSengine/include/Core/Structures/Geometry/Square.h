#pragma once

#include "Core/Structures/Geometry/Geometry.h"

class Square : public Geometry
{
public:
	ICS_API Square();
	ICS_API ~Square();

private:
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;
};