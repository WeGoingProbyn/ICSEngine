#pragma once

#include "Core/Structures/Scene/Mesh.h"
#include "Core/Structures/Scene/Root.h"
#include "Core/Structures/Buffers/Shaders.h"
#include "Core/Structures/Buffers/Constants.h"

class Entity
{
public:
	ICS_API Entity();
	ICS_API ~Entity();
	ICS_API Entity(Mesh* mesh, Shaders* shaders);

	inline Shaders& GetShaders() { return *m_Shaders; }
	inline Mesh& GetMesh() { return m_Root.GetMesh(); }
	inline Constants& GetConstants() { return m_ConstantBuffer; }
	inline darray<Node>& GetRootNodes() { return m_Root.GetNodes(); }
	inline void FlushConstants() { m_ConstantBuffer.GetBuffer().Flush(); }
	inline Transformation& GetBasdeTransform() { return m_Root.GetBaseTransform(); }
	inline Matrix<float, 4>& GetRootPropogated() { return m_Root.GetPropogatedTransform(); }
	inline void PropogateTransform(Transformation& transform) { m_Root.PropogateTransform(transform); }

	template<typename... Args>
	void PushConstants(Args&&... args);

private:
	Root m_Root;
	Shaders* m_Shaders;
	Constants m_ConstantBuffer;
}; 

template<typename... Args>
void Entity::PushConstants(Args&&... args)
{
	m_ConstantBuffer.PushConstantSet(std::move(args...));
}