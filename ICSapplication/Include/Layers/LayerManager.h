#pragma once

#include "Layers/Layer.h"
#include <Containers/array/darray.h>

class LayerManager
{
public:
	LayerManager();
	~LayerManager();

	template<typename T>
	T& Get();

	template<typename... Types>
	void PushLayer();
	template<typename T>
	void PushLayerToStack(T* type);
	template<typename First, typename... Rest>
	void PushLayerToStack(First* first, Rest*... rest);

	template<typename... Types>
	void DestroyLayers();
	template<typename T>
	void PopLayer();
	template<typename T>
	void QueryAndDestroy(T* type);
	template<typename First, typename... Rest>
	void QueryAndDestroy(First* first, Rest*... rest);
private:
	darray<Layer*> m_LayerStack;
};

template<typename T>
T& LayerManager::Get()
{
	for (unsigned int index = 0; index < m_LayerStack.Size(); index++)
	{
		T* ptr = dynamic_cast<T*>(m_LayerStack[index]);
		if (ptr != nullptr)
		{
			return *ptr;
		}
	}
	ICS_ERROR("LayerManager: Trying to get non existant layer type");
}

template<typename T>
void LayerManager::PushLayerToStack(T* type)
{
	ICS_ASSERT_MSG((std::is_base_of<Layer, T>::value), "LayerManager: Trying to push a layer type not derived from Layer base");
	Layer* ptr = reinterpret_cast<Layer*>(Memory::AllocateMemory<T>(sizeof(T), MemoryType::ICS_RENDERER));
	m_LayerStack.PushToEnd(ptr);
}

template<typename First, typename... Rest>
void LayerManager::PushLayerToStack(First* first, Rest*... rest)
{
	PushLayerToStack(first);
	PushLayerToStack(rest...);
}

template<typename... Types>
void LayerManager::PushLayer()
{
	PushLayerToStack(static_cast<Types*>(nullptr)...);
}

template<typename T>
void LayerManager::PopLayer()
{
	for (unsigned int index = 0; index < m_LayerStack.Size(); index++)
	{
		T* ptr = dynamic_cast<T*>(m_LayerStack[index]);
		if (ptr != nullptr)
		{
			Memory::FreeMemory(static_cast<T*>(m_LayerStack[index]), sizeof(T), MemoryType::ICS_RENDERER);
			m_LayerStack.PopAt(index);
		}
		else if (index == m_LayerStack.Last())
		{
			ICS_WARN("LayerManager: Trying to pop non existant layer type")
		}
	}
}

template<typename... Types>
void LayerManager::DestroyLayers()
{
	QueryAndDestroy(static_cast<Types*>(nullptr)...);
}

template<typename T>
void LayerManager::QueryAndDestroy(T* type)
{
	PopLayer<T>();
}

template<typename First, typename... Rest>
void LayerManager::QueryAndDestroy(First* first, Rest*... rest)
{
	QueryAndDestroy(first);
	QueryAndDestroy(rest...);
}
