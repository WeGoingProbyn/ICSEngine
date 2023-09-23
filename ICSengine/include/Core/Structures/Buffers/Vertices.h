#pragma once
#pragma once

#include <Containers/array/darray.h>
#include <Containers/Spatial/Vector.h>

class Vertices
{
public:
	enum Type
	{
		Vector2D,
		Vector3D,
		Texture2D,
		Normal,
		ColourF3,
		ColourF4,
		UnkownF2,
		UnkownF3,
		UnkownF4,
	};

public:
	class Layout
	{
	public:
		class Element
		{
		public:
			Element() : m_Type(Vertices::Type::UnkownF2), m_Offset(0) {}
			Element(Type type, unsigned int offset)
				:
				m_Type(type),
				m_Offset(offset) {}

			inline Type GetType() const { return m_Type; }
			static constexpr unsigned int SizeOfElement(Type type);
			inline unsigned int GetOffset() const { return m_Offset; }
			inline unsigned int GetSize() const { return SizeOfElement(m_Type); }
			inline unsigned int GetEndOfElement() const { return m_Offset + GetSize(); }
		private:
			Type m_Type;
			unsigned int m_Offset;
		};
	public:
		template<typename... Types>
		Layout(Types... args);

		ICS_API unsigned int Size();
		ICS_API bool PushTypeToEnd(Type type);
		ICS_API const Element& FindInStructure(Type type);

		inline Element& operator[](unsigned int index) { return m_VertexStructure[index]; }
	private:
		darray<Element> m_VertexStructure;
	};

public:
	class Vertex
	{
		friend class VertexBuffer;
	public:
		Vertex(char* ptr, Vertices::Layout& layout);

		template<typename T>
		bool PushVertex(unsigned int index, T&& value);
		template<typename First, typename... Rest>
		bool PushVertex(unsigned int index, First&& first, Rest&&... rest);
	
	private:
		template<typename Dest, typename Src>
		bool SetAttributeValue(char* ptr, Src&& value);
	private:
		char* m_Ptr;
		Vertices::Layout& m_Layout;
	};

private:
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(Layout layout);

		inline Layout& GetLayout() { return m_Layout; }
		inline char* GetBufferPointer() { return &m_ByteBlob[0]; }
		inline unsigned int GetNumberVertices() { return m_ByteBlob.Size() / m_Layout.Size(); }

		template<typename... Types>
		bool PushVertexToBuffer(Types&&... args);
		
		ICS_API Vertex End();
		ICS_API Vertex Begin();
		Vertex operator[](unsigned int index);
	private:
		Layout m_Layout;
		darray<char> m_ByteBlob;
	};
public:
	Vertices();
	Vertices(const Vertices& rhs);
	ICS_API Vertices(Layout layout);
	ICS_API const Vertices& operator=(const Vertices& rhs);

	inline VertexBuffer& GetBuffer() { return m_Buffer; }
	inline Layout& GetLayout() { return m_Buffer.GetLayout(); }
private:
	VertexBuffer m_Buffer;
};

constexpr unsigned int Vertices::Layout::Element::SizeOfElement(Vertices::Type type)
{
	switch (type)
	{
	case Vector2D:
		return sizeof(Vector<float, 2>);
	case Vector3D:
		return sizeof(Vector<float, 3>);
	case Texture2D:
		return sizeof(Vector<float, 2>);
	case Normal:
		return sizeof(Vector<float, 3>);
	case ColourF3:
		return sizeof(Vector<float, 3>);
	case ColourF4:
		return sizeof(Vector<float, 4>);
	case UnkownF2:
		return sizeof(Vector<float, 2>);
	case UnkownF3:
		return sizeof(Vector<float, 3>);
	case UnkownF4:
		return sizeof(Vector<float, 4>);
	}
	ICS_ERROR("Vertices: Undefined vertex element type");
	return 0;
}

template<typename... Types>
Vertices::Layout::Layout(Types... args)
	:
	m_VertexStructure(MemoryType::ICS_MODEL)
{
	//ICS_ASSERT_MSG(std::is_convertible<Types, Vertices::Layout::Element::Type>::value, "Vertices: Type mismatch on layout construction");
	(PushTypeToEnd(static_cast<Vertices::Type>(args)), ...);
	//(m_VertexStructure.PushToEnd(Vertices::Layout::Element(args)), ...);
}

template<typename... Types>
bool Vertices::VertexBuffer::PushVertexToBuffer(Types&&... args)
{
	m_ByteBlob.Resize(m_ByteBlob.Size() + m_Layout.Size());
	End().PushVertex(0u, std::forward<Types>(args)...);
	return true;
}

template<typename First, typename... Rest>
bool Vertices::Vertex::PushVertex(unsigned int index, First&& first, Rest&&... rest)
{
	PushVertex(index, std::forward<First>(first));
	PushVertex(index + 1, std::forward<Rest>(rest)...);
	return true;
}

template<typename T>
bool Vertices::Vertex::PushVertex(unsigned int index, T&& value)
{
	Vertices::Layout::Element& element = m_Layout[index];
	char* attribute = m_Ptr + element.GetOffset();
	if constexpr (std::is_same<std::remove_reference_t<decltype(value)>, Vector<float, 2>>::value)
	{
		switch (element.GetType())
		{
		case Vertices::Type::Vector2D:
		case Vertices::Type::Texture2D:
		case Vertices::Type::UnkownF2:
			SetAttributeValue<Vector<float, 2>>(attribute, std::forward<T>(value));
			return true;
		default:
			ICS_ERROR("Vertices: Vertex being pushed does not match layout description");
			return false;
		}
	}
	else if constexpr (std::is_same<std::remove_reference_t<decltype(value)>, Vector<float, 3>>::value)
	{
		switch (element.GetType())
		{
		case Vertices::Type::Normal:
		case Vertices::Type::Vector3D:
		case Vertices::Type::ColourF3:
		case Vertices::Type::UnkownF3:
			SetAttributeValue<Vector<float, 3>>(attribute, std::forward<T>(value));
			return true;
		default:
			ICS_ERROR("Vertices: Vertex being pushed does not match layout description");
			return false;
		}
	}
	else if constexpr (std::is_same<std::remove_reference_t<decltype(value)>, Vector<float, 4>>::value)
	{
		switch (element.GetType())
		{
		case Vertices::Type::ColourF4:
		case Vertices::Type::UnkownF4:
			SetAttributeValue<Vector<float, 4>>(attribute, std::forward<T>(value));
			return true;
		default:
			ICS_ERROR("Vertices: Vertex being pushed does not match layout description");
			return false;
		}
	}
	else
	{
		ICS_ERROR("Vertices: Vector dimension miss match, dimensions can be <float, 2> -> <float, 4>");
		return false;
	}
}

template<typename Dest, typename Src>
bool Vertices::Vertex::SetAttributeValue(char* ptr, Src&& value)
{
	if constexpr (std::is_assignable<Dest, Src>::value)
	{
		*reinterpret_cast<Dest*>(ptr) = value;
		return true;
	}
	else
	{
		ICS_ERROR("Vertices: Type mismatch during attribute assignment");
		return false;
	}
}