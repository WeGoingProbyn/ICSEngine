#include "Core/Structures/Scene/Entity.h"

Entity::Entity()
{
}

Entity::Entity(Mesh* mesh, Shaders* shaders)
	:
	m_Root(mesh),
	m_Shaders(shaders),
	m_ConstantBuffer(shaders->GetConstLayout())
{
	m_Root.SetBaseTransform(mesh->GetTransforms()[0]);
	for (unsigned int index = 0; index < m_Root.GetNodes().Size(); index++)
	{
		// NOTE: This assumes nodes are all in the same appended 
		// NOTE: oreder. this may Cause trouble at some point!!
		m_Root.GetNodes()[index].SetBaseTransform(mesh->GetTransforms()[index + 1]);
	}
}

Entity::~Entity()
{
	// Entity doesn't need to own this pointer, it is held globally
	// Need to make sure it is properly dereferenced when done with it
	m_Shaders = nullptr;
}