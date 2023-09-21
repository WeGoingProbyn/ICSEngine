#include "Graphics/RenderFront/Buffers/Vertices.h"


const Vertices::Layout::Element& Vertices::Layout::FindInStructure(Vertices::Type type)
{
	for (const Vertices::Layout::Element& element : m_VertexStructure)
	{
		if (element.GetType() == type)
		{
			return element;
		}
	}
	ICS_ERROR("Vertices: Element type does not exist in defined structure");
	return m_VertexStructure[0];
}

bool Vertices::Layout::PushTypeToEnd(Vertices::Type type)
{
	if (m_VertexStructure.Size() == 0)
	{
		m_VertexStructure.PushToEnd({ type, 0u });
		return true;
	}
	else
	{
		const Element& element = m_VertexStructure[m_VertexStructure.Last()];
		m_VertexStructure.PushToEnd({ type, element.GetSize() + element.GetOffset() });
		return true;
	}
}


unsigned int Vertices::Layout::Size()
{
	return m_VertexStructure.Size() > 0 ? m_VertexStructure[m_VertexStructure.Last()].GetEndOfElement() : 0u;
}

Vertices::Vertex::Vertex(char* ptr, Vertices::Layout& layout)
	:
	m_Ptr(ptr),
	m_Layout(layout)
{
}

Vertices::VertexBuffer::VertexBuffer(Layout layout)
	:
	m_Layout(layout)
{
}

Vertices::VertexBuffer::VertexBuffer()
{
}

Vertices::Vertex Vertices::VertexBuffer::End()
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on End");
	return Vertex{ &m_ByteBlob[0] + m_ByteBlob.Size() - m_Layout.Size(), m_Layout };
}

Vertices::Vertex Vertices::VertexBuffer::Begin()
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on Begin");
	return Vertex{ &m_ByteBlob[0], m_Layout };
}

Vertices::Vertex Vertices::VertexBuffer::operator[](unsigned index)
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on operator[]");
	return Vertex{ &m_ByteBlob[0] + m_Layout.Size() * index, m_Layout };
}


Vertices::Vertices()
{
}

Vertices::Vertices(Vertices::Layout layout)
	:
	m_Buffer(layout)
{
}

Vertices::Vertices(const Vertices& rhs)
{
	*this = rhs;
}

const Vertices& Vertices::operator=(const Vertices& rhs)
{
	m_Buffer = rhs.m_Buffer;
	return *this;
}