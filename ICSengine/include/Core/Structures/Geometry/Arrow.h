#pragma once

#include "Core/Structures/Geometry/Cone.h"
#include "Core/Structures/Geometry/Cylinder.h"
#include "Core/Structures/Geometry/Geometry.h"
#include "Core/Structures/Spatial/Transformation.h"

class Arrow : public Geometry
{
public:
	ICS_API Arrow();
	ICS_API ~Arrow();
	//ICS_API Arrow(unsigned int faces);

private:
	ICS_API bool FindIndices() override;
	ICS_API bool FindVertices() override;
	ICS_API bool FindNormals() override;

private:
	Cone m_Tip;
	Cylinder m_Base;
	Indices::Hierachy m_Hierachy;
};