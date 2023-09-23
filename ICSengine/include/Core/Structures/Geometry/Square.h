#pragma once

#include "Core/Structures/Geometry/Geometry.h"

class Square : public Geometry
{
public:
	ICS_API Square();
	ICS_API ~Square();

private:
	bool FindIndices() override;
	bool FindVertices() override;
};