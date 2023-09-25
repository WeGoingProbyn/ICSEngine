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
			Element() : m_ID(0u), m_Offset(0u), m_BlockSize(0u), m_Root(0u), m_PrimitiveType(Indices::Type::TriangleList) {}
			Element(unsigned int id, unsigned int offset, unsigned int size, Indices::Type type) 
				: 
				m_ID(id), 
				m_Root(0u),
				m_Offset(offset), 
				m_BlockSize(size), 
				m_PrimitiveType(type),
				m_Nodes(MemoryType::ICS_MODEL)
			{}
			Element(unsigned int id, unsigned int offset, unsigned int size, unsigned int root, Indices::Type type) :
				m_ID(id), 
				m_Root(root), 
				m_Offset(offset), 
				m_BlockSize(size), 
				m_PrimitiveType(type),
				m_Nodes(MemoryType::ICS_MODEL)
			{}

			~Element()
			{
			}

			static constexpr unsigned int SizeOfPrimitive(Type type);

			inline unsigned int GetID() { return m_ID; }
			inline unsigned int GetRootID() { return m_Root; }
			inline unsigned int GetOffset() { return m_Offset; }
			inline unsigned int GetBlockSize() { return m_BlockSize; }
			inline Indices::Type GetType() { return m_PrimitiveType; }
			inline darray<unsigned int>& GetNodeIDs() { return m_Nodes; }
			inline unsigned int GetEndOfElement() { return m_Offset + GetSize(); }
			inline unsigned int GetElementStride() { return SizeOfPrimitive(m_PrimitiveType); }
			inline unsigned int GetSize() { return GetElementStride() * m_BlockSize; }
		private:
			unsigned int m_Root;
			darray<unsigned int> m_Nodes;

			unsigned int m_ID;
			unsigned int m_Offset;
			unsigned int m_BlockSize;
			
			Indices::Type m_PrimitiveType;
		};
	public:
		ICS_API Hierachy();

		//template<typename... Types>
		//Hierachy(Types&&... args);

		ICS_API inline darray<Element>& GetHierachy() { return m_IndexHierachy; }
		ICS_API inline unsigned int GetTotalDescribedNodes() { return m_IndexHierachy.Size(); }
		ICS_API inline Element& operator[](unsigned int index) { return m_IndexHierachy[index]; }
		ICS_API void PushNodeToHierachy(unsigned int size, unsigned int root_id, Indices::Type type);
	private:
		unsigned int m_UniqueRoots;
		darray<Element> m_IndexHierachy;
	};

public:
	class Node
	{
		friend class IndexBuffer;
	public:
		Node(char* ptr, Indices::Hierachy& structure, unsigned int id);
		
		template<typename T>
		void PushNode(unsigned int id, darray<T>&& indices);

		inline unsigned int GetID() { return m_ID; }
		inline const char* GetNodePointer() const { return m_Ptr; }
		inline Indices::Hierachy& GetNodeHierachy() { return m_Hierachy; }
		inline darray<unsigned int>& GetNodes() { return m_Hierachy[m_ID].GetNodeIDs(); }

		inline unsigned int GetSize() { return m_Hierachy[m_ID].GetSize(); }
	private:
		template<typename Dest, typename Src>
		bool SetNodeValue(char* ptr, darray<Src>&& value);
	private:
		char* m_Ptr;
		unsigned int m_ID;
		Indices::Hierachy& m_Hierachy;
	};

public:
	class IndexBuffer
	{
	public:
		ICS_API IndexBuffer() : m_ByteBlob(MemoryType::ICS_MODEL), m_TotalBufferedNodes(0u) {}
		ICS_API IndexBuffer(Hierachy& hierachy);

		ICS_API Node End();
		ICS_API Node Begin();
		ICS_API Node operator[](unsigned int index);

		inline Indices::Hierachy& GetHierachy() { return m_Hierachy; }

		template<typename T>
		void PushNodeToBuffer(darray<T>& indices);
		template<typename T>
		void PushNodeToBuffer(darray<T>&& indices);
	private:
		darray<char> m_ByteBlob;
		Indices::Hierachy m_Hierachy;
		unsigned int m_TotalBufferedNodes;
	};
public:
	Indices() {}

	Indices(const Indices& rhs);
	ICS_API Indices(Hierachy hierachy);
	ICS_API const Indices& operator=(const Indices& rhs);

	inline IndexBuffer& GetBuffer() { return m_Buffer; }
	inline Hierachy& GetHierachy() { return m_Buffer.GetHierachy(); }

private:
	IndexBuffer m_Buffer;
};

template<typename T>
void Indices::Node::PushNode(unsigned int id, darray<T>&& indices)
{
	ICS_ASSERT_MSG(id < m_Hierachy.GetTotalDescribedNodes(), "Indices: Trying to push more nodes than layout has described");

	Indices::Hierachy::Element& element = m_Hierachy[id];
	char* attribute = m_Ptr + element.GetOffset();
	if constexpr (std::is_same<T, unsigned int>::value)
	{
		switch (element.GetType())
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
		switch (element.GetType())
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
		switch (element.GetType())
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
bool Indices::Node::SetNodeValue(char* ptr, darray<Src>&& value)
{
	if constexpr (std::is_assignable<Dest, Src>::value)
	{
		for (unsigned int index = 0; index < value.Size(); index++)
		{
			*reinterpret_cast<Dest*>(ptr + (index * sizeof(Src))) = value[index];
		}
		return true;
	}
	else
	{
		ICS_ERROR("Vertices: Type mismatch during attribute assignment");
		return false;
	}
}

template<typename T>
void Indices::IndexBuffer::PushNodeToBuffer(darray<T>&& indices)
{
	m_ByteBlob.Resize(m_ByteBlob.Size() + indices.Size() * sizeof(T));
	End().PushNode(m_Hierachy.GetHierachy()[m_TotalBufferedNodes].GetID(), std::forward<darray<T>>(indices));
	m_TotalBufferedNodes++;

}

template<typename T>
void Indices::IndexBuffer::PushNodeToBuffer(darray<T>& indices)
{
	m_ByteBlob.Resize(m_ByteBlob.Size() + indices.Size() * sizeof(T));
	End().PushNode(m_Hierachy.GetHierachy()[m_TotalBufferedNodes].GetID(), std::forward<darray<T>>(indices));
	m_TotalBufferedNodes++;

}

constexpr unsigned int Indices::Hierachy::Element::SizeOfPrimitive(Indices::Type type)
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
