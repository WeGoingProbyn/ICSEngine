#pragma once

#include "Containers/array/darray.h"
#include "Graphics/RenderFront/Spatial/Transformation.h"

class Node
{
public:
	Node() {}

	inline darray<Node>& GetNodes() { return m_Nodes; }
	inline Transformation& GetRelativeTransform() { return m_RelativeTransform; }
private:
	darray<Node> m_Nodes;
	Transformation m_RelativeTransform;
};