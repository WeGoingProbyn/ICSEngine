#pragma once

#include <Containers/array/darray.h>
#include <Containers/String/String.h>
#include <Containers/Spatial/Vector.h>

class Indices
{
public:
	enum Type
	{
		PointList,
		LineStrip,
		LineList,
		TriangleList
		// TODO: Triangle Strips
	};

public:
	class Hierachy
	{
	public:
		class Element
		{
		public:
			Element() : m_ID(0u), m_Offset(0u), m_BlockSize(0u), m_Root(0u), m_PrimitiveStride(0u) {}
			Element(unsigned int id, unsigned int offset, unsigned int size, unsigned int stride)
				: 
				m_ID(id), 
				m_Root(0u),
				m_Offset(offset), 
				m_BlockSize(size), 
				m_PrimitiveStride(stride),
				m_Nodes(MemoryType::ICS_MODEL)
			{}
			Element(unsigned int id, unsigned int offset, unsigned int size, unsigned int root, unsigned int stride) :
				m_ID(id), 
				m_Root(root), 
				m_Offset(offset), 
				m_BlockSize(size), 
				m_PrimitiveStride(stride),
				m_Nodes(MemoryType::ICS_MODEL)
			{}

			~Element()
			{
			}


			inline unsigned int GetID() { return m_ID; }
			inline unsigned int GetRootID() { return m_Root; }
			inline unsigned int GetOffset() { return m_Offset; }
			inline unsigned int GetBlockSize() { return m_BlockSize; }
			inline darray<unsigned int>& GetNodeIDs() { return m_Nodes; }
			inline unsigned int GetEndOfElement() { return m_Offset + GetSize(); }
			inline unsigned int GetSize() { return m_PrimitiveStride * m_BlockSize; }
		private:
			unsigned int m_Root;
			darray<unsigned int> m_Nodes;

			unsigned int m_ID;
			unsigned int m_Offset;
			unsigned int m_BlockSize;
			unsigned int m_PrimitiveStride;
		};
	public:
		ICS_API Hierachy();
		ICS_API Hierachy(Indices::Type type);

		ICS_API inline darray<Element>& GetHierachy() { return m_IndexHierachy; }
		ICS_API inline unsigned int GetTotalDescribedNodes() { return m_IndexHierachy.Size(); }
		ICS_API inline Element& operator[](unsigned int index) { return m_IndexHierachy[index]; }

		static constexpr unsigned int SizeOfPrimitive(Type type);
		inline Indices::Type GetType() { return m_PrimitiveType; }
		ICS_API void PushNodeToHierachy(unsigned int size, unsigned int root_id);
		inline unsigned int GetElementStride() { return SizeOfPrimitive(m_PrimitiveType); }
		inline unsigned int NumberPointsInPrimitive() { return GetElementStride() / sizeof(unsigned int); }
	private:
		unsigned int m_UniqueRoots;
		Indices::Type m_PrimitiveType;
		darray<Element> m_IndexHierachy;
	};

public:
	class Node
	{
		friend class IndexBuffer;
	public:
		Node(unsigned int* ptr, Indices::Hierachy& structure, unsigned int id);
		
		template<typename T>
		void PushNode(unsigned int id, darray<T>&& indices);

		inline unsigned int GetID() { return m_ID; }
		inline Indices::Hierachy& GetNodeHierachy() { return m_Hierachy; }
		inline const unsigned int* GetNodePointer() const { return m_Ptr; }
		inline darray<unsigned int>& GetNodes() { return m_Hierachy[m_ID].GetNodeIDs(); }

		//inline unsigned int GetSize() { return m_Hierachy[m_ID].GetSize(); }
	private:
		template<typename Dest, typename Src>
		bool SetNodeValue(unsigned int* ptr, darray<Src>&& value);
	private:
		unsigned int m_ID;
		unsigned int* m_Ptr;
		Indices::Hierachy& m_Hierachy;
	};

public:
	class IndexBuffer
	{
	public:
		ICS_API IndexBuffer() : m_Nodes(MemoryType::ICS_MODEL), m_TotalBufferedNodes(0u) {}
		ICS_API IndexBuffer(Hierachy& hierachy);

		ICS_API Node End();
		ICS_API Node Begin();
		ICS_API Node operator[](unsigned int index);

		inline Indices::Hierachy& GetHierachy() { return m_Hierachy; }

		//template<typename T>
		//void PushNodeToBuffer(darray<T>& indices);
		template<typename T>
		void PushNodeToBuffer(darray<T>&& indices);
	private:
		Indices::Hierachy m_Hierachy;
		unsigned int m_TotalBufferedNodes;
		darray<darray<unsigned int>> m_Nodes;
	};
public:
	class Iterator {
	public:
		Iterator(Indices& indices, unsigned int start = 0) : BufferRef(indices), index(start) {}

		// Define iterator operations
		void operator++() { index++; }
		Node operator*() { return BufferRef.GetBuffer()[index]; }
		bool operator!=(const Iterator& other) const { return index != other.index; }
	private:
		unsigned int index;
		Indices& BufferRef;
	};

	// Functions to get iterators
	Iterator begin()
	{
		return Iterator(*this);
	}

	Iterator end() 
	{
		return Iterator(*this, m_Buffer.GetHierachy().GetTotalDescribedNodes());
	}

	Indices() {}

	ICS_API Indices(const Indices& rhs);
	ICS_API Indices(Hierachy hierachy);
	ICS_API const Indices& operator=(const Indices& rhs);
	ICS_API ~Indices() {}

	template<typename T>
	inline void PushNode(darray<T>&& indices) { m_Buffer.PushNodeToBuffer(std::forward<darray<T>>(indices)); }
	inline IndexBuffer& GetBuffer() { return m_Buffer; }
	inline Hierachy& GetHierachy() { return m_Buffer.GetHierachy(); }

	ICS_API Node operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

private:
	IndexBuffer m_Buffer;
};

template<typename T>
void Indices::Node::PushNode(unsigned int id, darray<T>&& indices)
{
	ICS_ASSERT_MSG(id < m_Hierachy.GetTotalDescribedNodes(), "Indices: Trying to push more nodes than layout has described");

	Indices::Hierachy::Element& element = m_Hierachy[id];
	auto x = element.GetOffset() / sizeof(unsigned int);
	unsigned int* attribute = m_Ptr;
	if constexpr (std::is_same<T, unsigned int>::value)
	{
		switch (m_Hierachy.GetType())
		{
		case Indices::Type::LineList:
		case Indices::Type::PointList:
			SetNodeValue<unsigned int>(attribute, std::forward<darray<T>>(indices));
			break;
		default:
			ICS_ERROR("Indices: Node being pushed does not match layout description");
			break;
		}
	}
	if constexpr (std::is_same<T, Vector<unsigned int, 2>>::value)
	{
		switch (m_Hierachy.GetType())
		{
		case Indices::Type::LineStrip:
			SetNodeValue<Vector<unsigned int, 2>>(attribute, std::forward<darray<T>>(indices));
			break;
		default:
			ICS_ERROR("Indices: Node being pushed does not match layout description");
			break;
		}
	}
	else if constexpr (std::is_same<T, Vector<unsigned int, 3>>::value)
	{
		switch (m_Hierachy.GetType())
		{
		case Indices::Type::TriangleList:
			SetNodeValue<Vector<unsigned int, 3>>(attribute, std::forward<darray<T>>(indices));
			break;
		default:
			ICS_ERROR("Indices: Node being pushed does not match layout description");
			break;
		}
	}
	else
	{
		ICS_ERROR("Indices: Node dimension miss match, dimensions can be unsigned int -> <unsigned int, 3>");
	}
}

template<typename Dest, typename Src>
bool Indices::Node::SetNodeValue(unsigned int* ptr, darray<Src>&& value)
{
	if constexpr (std::is_assignable<Dest, Src>::value)
	{
		for (unsigned int index = 0; index < value.Size(); index++)
		{
			*reinterpret_cast<Dest*>(ptr + (index * (sizeof(Src) / sizeof(unsigned int)))) = value[index];
		}
		return true;
	}
	else
	{
		ICS_ERROR("Indices: Type mismatch during attribute assignment");
		return false;
	}
}

template<typename T>
void Indices::IndexBuffer::PushNodeToBuffer(darray<T>&& indices)
{
	m_Nodes.PushToEnd({ });
	m_Nodes[m_Nodes.Last()].Resize(indices.Size() * (sizeof(T) / sizeof(unsigned int)));
	End().PushNode(m_Hierachy.GetHierachy()[m_TotalBufferedNodes].GetID(), std::forward<darray<T>>(indices));
	m_TotalBufferedNodes++;

}

//template<typename T>
//void Indices::IndexBuffer::PushNodeToBuffer(darray<T>& indices)
//{
//	m_Nodes.PushToEnd({ });
//	m_Nodes[m_Nodes.Last()].Resize(indices.Size() * (sizeof(T) / sizeof(unsigned int)));
//	End().PushNode(m_Hierachy.GetHierachy()[m_TotalBufferedNodes].GetID(), std::move(indices));
//	m_TotalBufferedNodes++;
//
//}

constexpr unsigned int Indices::Hierachy::SizeOfPrimitive(Indices::Type type)
{
	switch (type)
	{
	case PointList:
	case LineStrip:
		return sizeof(unsigned int);
	case LineList:
		return sizeof(Vector<unsigned int, 2>);
	case TriangleList:
		return sizeof(Vector<unsigned int, 3>);
	}
	ICS_ERROR("Vertices: Undefined vertex element type");
	return 0;
}
