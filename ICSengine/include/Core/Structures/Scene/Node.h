#pragma once

#include "Containers/array/darray.h"
#include "Core/Structures/Buffers/Indices.h"
#include "Core/Structures/Spatial/Transformation.h"

class Node
{
public:
	ICS_API Node();
	ICS_API Node(Indices::Node indices);

	inline darray<Node>& GetNodes() { return m_Nodes; }
	inline Transformation& GetBaseTransform() { return m_BaseTransform; }
	inline Transformation& GetRelativeTransform() { return m_RelativeTransform; }
protected:
	darray<Node> m_Nodes;
	Transformation m_BaseTransform;
	Transformation m_RelativeTransform;
};