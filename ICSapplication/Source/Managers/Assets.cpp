#include "Managers/Assets.h"

Manager<Mesh>* Assets::m_MeshStack = nullptr;
Manager<Shaders>* Assets::m_ShaderStack = nullptr;

void Assets::OnStartUp()
{
	m_MeshStack = Memory::AllocateMemory<Manager<Mesh>>(1u, MemoryType::ICS_STACK_MANAGER);
	m_ShaderStack = Memory::AllocateMemory<Manager<Shaders>>(1u, MemoryType::ICS_STACK_MANAGER);
}

void Assets::OnShutDown()
{
	Memory::FreeMemory(m_MeshStack, 1u, MemoryType::ICS_STACK_MANAGER);
	Memory::FreeMemory(m_ShaderStack, 1u, MemoryType::ICS_STACK_MANAGER);
}