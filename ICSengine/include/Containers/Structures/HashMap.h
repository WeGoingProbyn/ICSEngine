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
	Value& operator[](const Key& key);

	int Exists(Key& key);
	bool Remove(Key& key);
	bool Insert(Key& key, Value& value);

private:
	float m_LoadFactor;
	darray<darray<HashMap::Pair>> m_Map;
};

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap()
	:
	m_Map(),
	m_LoadFactor(0.7f)
{
	m_Map.Resize(50);
}

template<typename Key, typename Value>
Value& HashMap<Key, Value>::operator[](const Key& key)
{
	if (Exists(key)) { return m_Map[key.Hash() % m_Map.Size()].value; }
	else 
	{ 
		ICS_WARN("HashMap: Key does not exist in HashMap, Returned Map[0][0].value")
		return m_Map[0][0].value;
	}
}

template<typename Key, typename Value>
int HashMap<Key, Value>::Exists(Key& key)
{
	unsigned int index = key.GetHashValue() % m_Map.Size();
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
	unsigned int index = Exists(key);
	if (index > -1)
	{
		m_Map.PopAt(key.GetHashValue() % m_Map.Size());
		return true;
	}
	else
	{
		ICS_WARN("HashMap: Trying to Remove a non existant key value pair");
		return false;
	}
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Insert(Key& key, Value& value)
{
	unsigned int index = Exists(key);
	if (index > -1)
	{
		ICS_WARN("HashMap: Trying to Insert a duplicate key");
		return false;
	}
	else
	{
		m_Map[key.GetHashValue() % m_Map.Size()].PushToEnd(HashMap<Key, Value>::Pair(key, value));
		
		unsigned int i = 0u;
		if (m_Map[key.GetHashValue() % m_Map.Size()].Last() > 0)
		{
			i = m_Map[key.GetHashValue() % m_Map.Size()].Last();
		}
		
		m_Map[key.GetHashValue() % m_Map.Size()][i].index = i;
		return true;
	}
}
