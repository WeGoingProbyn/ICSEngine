#pragma once

#include "Containers/array/darray.h"
#include "Containers/Types/Hashable.h"

// Note: The Key object type must be derived from Container/Types/Hashable
// Note: Or already have an intrinsically defined hash function

template<typename Key, typename Value>
class HashMap
{
public:
	struct Pair
	{
		Key key;
		Value value;
		unsigned int index;

		Pair() : key(), value(), index(0) {}
		Pair(Key k, Value v) : key(k), value(v), index(0) {}
	};
public:
	HashMap();
	HashMap(MemoryType type);
	Value& operator[](Key&& key);

	inline darray<Key>& GetLiveKeys() { return m_ActiveKeys; }
	inline unsigned int GetNumberPairs() { return m_TotalPairs; }

	bool Exists(Key& key);
	bool Remove(Key& key);
	bool Insert(Key& key, Value& value);
	bool Insert(Key&& key, Value value);
	bool Insert(Key&& key, Value&& value);

private:
	bool Resize();
	int ExistsWhere(Key& key);
	bool Emplace(Key& key, Value& value);
private:
	float m_LoadFactor;
	darray<Key> m_ActiveKeys;
	unsigned int m_TotalPairs;
	darray<darray<HashMap::Pair>> m_Map;
};

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap()
	:
	m_TotalPairs(0u),
	m_LoadFactor(0.7f)
{
	m_Map.Resize(10);
}

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(MemoryType type)
	:
	m_Map(type),
	m_TotalPairs(0u),
	m_LoadFactor(0.7f),
	m_ActiveKeys(type)
{
	m_Map.Resize(10);
}

template<typename Key, typename Value>
Value& HashMap<Key, Value>::operator[](Key&& key)
{
	Hashable<Key> hash(key);
	int index = ExistsWhere(key);
	ICS_ASSERT_MSG(index > -1, "HashMap: Trying to access non existant Key in HashMap");
	return m_Map[hash.GetHashValue() % m_Map.Size()][index].value;
}

template<typename Key, typename Value>
int HashMap<Key, Value>::ExistsWhere(Key& key)
{
	Hashable<Key> hash(key);
	unsigned int index = hash.GetHashValue() % m_Map.Size();
	if (!m_TotalPairs)
	{
		return -1;
	}
	for (unsigned int indent = 0; indent < m_Map[index].Size(); indent++)
	{
		if (m_Map[index][indent].key == key)
		{
			return indent;
		}
	}
	return -1;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Remove(Key& key)
{
	Hashable<Key> hash(key);
	int index = ExistsWhere(key);
	if (index > -1)
	{
		m_Map[hash.GetHashValue() % m_Map.Size()].PopAt(index);
		for (unsigned int index = 0; index < m_ActiveKeys.Size(); index++)
		{
			if (m_ActiveKeys[index] == key)
			{
				m_ActiveKeys.PopAt(index);
			}
		}
		m_TotalPairs--;
		return true;
	}
	else
	{
		ICS_WARN("HashMap: Trying to Remove a non existant key value pair");
		return false;
	}
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Insert(Key&& key, Value&& value)
{
	if (m_TotalPairs > m_Map.Allocated() * m_LoadFactor)
	{
		Resize();
	}
	int index = ExistsWhere(key);
	if (index > -1)
	{
		ICS_WARN("HashMap: Trying to Insert a duplicate key");
		return false;
	}
	else
	{
		Emplace(key, value);
		m_ActiveKeys.PushToEnd(key);
		return true;
	}
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Insert(Key& key, Value& value)
{
	if (m_TotalPairs > m_Map.Allocated() * m_LoadFactor)
	{
		Resize();
	}
	int index = ExistsWhere(key);
	if (index > -1)
	{
		ICS_WARN("HashMap: Trying to Insert a duplicate key");
		return false;
	}
	else
	{
		Emplace(key, value);
		m_ActiveKeys.PushToEnd(key);
		return true;
	}
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Emplace(Key& key, Value& value)
{
	Hashable<Key> hash(key);
	m_Map[hash.GetHashValue() % m_Map.Size()].PushToEnd({ key, value });
	
	unsigned int i = 0u;
	if (m_Map[hash.GetHashValue() % m_Map.Size()].Last() > 0)
	{
		i = m_Map[hash.GetHashValue() % m_Map.Size()].Last();
	}

	m_Map[hash.GetHashValue() % m_Map.Size()][i].index = i;
	m_TotalPairs++;
	return true;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Resize()
{
	darray<darray<HashMap::Pair>>* ptr = Memory::AllocateMemory<darray<darray<HashMap::Pair>>>(1u, MemoryType::ICS_STACK_MANAGER);
	auto& tmp = *ptr;
	tmp.Resize(m_Map.Allocated() * 2u);

	for (darray<HashMap<Key, Value>::Pair>& pairs : m_Map)
	{
		for (HashMap<Key, Value>::Pair& pair : pairs)
		{
			Hashable<Key> hash(pair.key);
			tmp[hash.GetHashValue() % tmp.Size()].PushToEnd({ pair.key, pair.value });

			unsigned int i = 0u;
			if (tmp[hash.GetHashValue() % tmp.Size()].Last() > 0)
			{
				i = tmp[hash.GetHashValue() % tmp.Size()].Last();
			}
			tmp[hash.GetHashValue() % tmp.Size()][i].index = i;
		}
	}
	m_Map = *ptr;
	Memory::FreeMemory(ptr, 1u, MemoryType::ICS_STACK_MANAGER);
	return true;
}