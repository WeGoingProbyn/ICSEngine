#pragma once

#include "Containers/array/darray.h"
#include "Core/Structures/Buffers/Indices.h"
#include "Core/Structures/Spatial/Transformation.h"

class Node
{
public:
	ICS_API Node();
	ICS_API Node(Indices::Node indices);
	ICS_API void PropogateTransform(Transformation& accumulated);
	ICS_API void PropogateTransform(Matrix<float, 4> accumulated);

	inline darray<Node>& GetNodes() { return m_Nodes; }
	inline Transformation& GetBaseTransform() { return m_BaseTransform; }
	inline Matrix<float, 4>& GetPropogatedTransform() { return m_RelativeTransform; }
protected:
	darray<Node> m_Nodes;
	Transformation m_BaseTransform;
	Matrix<float, 4> m_RelativeTransform;
};