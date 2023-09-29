#pragma once

#include "Managers/Manager.h"
#include <Core/Structures/Scene/Mesh.h>
#include <Core/Structures/Buffers/Shaders.h>

class ICS_API Assets
{
public:
	template<typename T>
	static T& Get(String&& key);
	template<typename T>
	static T& Get(const char* key);

	template<typename T>
	static void PushToStack(String&& name);
	template<typename T, typename... Args>
	static void PushToStack(String&& name, Args... args);

	static void OnStartUp();
	static void OnShutDown();

private:
	Assets() {}
	Assets(const Assets& rhs) = delete;
	const Assets& operator=(const Assets& rhs) = delete;

private:
	static Manager<Mesh>* m_MeshStack;
	static Manager<Shaders>* m_ShaderStack;
};

template<typename T>
T& Assets::Get(String&& key)
{
	if constexpr (std::is_same<T, Mesh>::value)
	{
		return Assets::m_MeshStack->operator[](std::move(key));
	}
	else if constexpr (std::is_same<T, Shaders>::value)
	{
		return Assets::m_ShaderStack->operator[](std::move(key));
	}
	else
	{
		ICS_ERROR("Assets: Trying to retrieve an unkown asset type");
	}
}

template<typename T>
T& Assets::Get(const char* key)
{
	String str(key);
	return Get<T>(std::move(str));
}

template<typename T>
void Assets::PushToStack(String&& name)
{
	if constexpr (std::is_same<T, Mesh>::value)
	{
		Assets::m_MeshStack->PushToStack(name);
	}
	else if constexpr (std::is_same<T, Mesh>::value)
	{
		Assets::m_ShaderStack->PushToStack(name);
	}
	else
	{
		ICS_ERROR("Assets: Trying to push an unkown asset type");
	}
}

template<typename T, typename... Args>
void Assets::PushToStack(String&& name, Args... args)
{
	T tmp = T(args...);
	if constexpr (std::is_base_of<Mesh, T>::value || std::is_same<T, Mesh>::value)
	{
		Assets::m_MeshStack->PushToStack(std::move(name), args...);
	}
	else if constexpr (std::is_same<T, Shaders>::value)
	{
		Assets::m_ShaderStack->PushToStack(std::move(name), args...);
	}
	else
	{
		ICS_ERROR("Assets: Trying to push an unkown asset type");
	}
}