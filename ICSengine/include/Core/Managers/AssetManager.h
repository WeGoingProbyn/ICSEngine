#pragma once

#include "Core/Managers/Manager.h"
#include "Core/Structures/Scene/Mesh.h"

class AssetManager
{
public:
	static AssetManager& Assets() { static AssetManager mng; return mng; }

	template<typename T>
	T& Get(String&& key);
	template<typename T>
	T& Get(const char* key);

	template<typename T>
	void PushToStack(String&& name);
	template<typename T, typename... Args>
	void PushToStack(String&& name, Args... args);

	inline void OnShutDown()
	{
		m_MeshStack.~Manager();
		m_ShaderStack.~Manager();
	}

private:
	AssetManager() {}
	~AssetManager() {}
	AssetManager(const AssetManager& rhs) = delete;
	const AssetManager& operator=(const AssetManager& rhs) = delete;

private:
	Manager<Mesh> m_MeshStack;
	Manager<Shaders> m_ShaderStack;
};

template<typename T>
T& AssetManager::Get(String&& key)
{
	if constexpr (std::is_same<T, Mesh>::value)
	{
		return m_MeshStack[std::move(key)];
	}
	else if constexpr (std::is_same<T, Shaders>::value)
	{
		return m_ShaderStack[std::move(key)];
	}
	else
	{
		ICS_ERROR("AssetManager: Trying to retrieve an unkown asset type");
	}
}

template<typename T>
T& AssetManager::Get(const char* key)
{
	String str(key);
	return Get<T>(std::move(str));
}

template<typename T>
void AssetManager::PushToStack(String&& name)
{
	if constexpr (std::is_same<T, Mesh>::value)
	{
		m_MeshStack.PushToStack(name);
	}
	else if constexpr (std::is_same<T, Mesh>::value)
	{
		m_ShaderStack.PushToStack(name);
	}
	else
	{
		ICS_ERROR("AssetManager: Trying to push an unkown asset type");
	}
}

template<typename T, typename... Args>
void AssetManager::PushToStack(String&& name, Args... args)
{
	T tmp = T(args...);
	if constexpr (std::is_base_of<Mesh, T>::value || std::is_same<T, Mesh>::value)
	{
		m_MeshStack.PushToStack(std::move(name), args...);
	}
	else if constexpr (std::is_same<T, Shaders>::value)
	{
		m_ShaderStack.PushToStack(std::move(name), args...);
	}
	else
	{
		ICS_ERROR("AssetManager: Trying to push an unkown asset type");
	}
}