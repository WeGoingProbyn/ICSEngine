#include "Core/Structures/Buffers/Indices.h"

void Indices::Hierachy::PushNodeToHierachy(unsigned int size, unsigned int root_id, Indices::Type type)
{
	if (m_IndexHierachy.Size() > 0)
	{
		m_IndexHierachy.PushToEnd(Indices::Hierachy::Element(m_IndexHierachy.Size(), m_IndexHierachy[m_IndexHierachy.Last()].GetEndOfElement(), size, root_id, type));
	}
	else
	{
		m_IndexHierachy.PushToEnd(Indices::Hierachy::Element(0u, 0u, size, root_id, type));

	}

	if (root_id != m_IndexHierachy.Last())
	{
		m_IndexHierachy[root_id].GetNodeIDs().PushToEnd(m_IndexHierachy.Last());
	}
}

Indices::Node::Node(char* ptr, Indices::Hierachy& hierachy, unsigned int id)
	:
	m_ID(id),
	m_Ptr(ptr),
	m_Hierachy(hierachy)
{
}

Indices::Node Indices::IndexBuffer::End()
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on End");
	return Node{ &m_ByteBlob[0] + m_ByteBlob.Size() - m_Hierachy.GetHierachy()[m_TotalBufferedNodes].GetSize(), m_Hierachy, m_TotalBufferedNodes };
}

Indices::Node Indices::IndexBuffer::Begin()
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on Begin");
	return Node{ &m_ByteBlob[0], m_Hierachy, 0u };
}

Indices::Node Indices::IndexBuffer::operator[](unsigned int index)
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on operator[]");
	return Node{ &m_ByteBlob[0] + m_Hierachy.GetHierachy()[index].GetOffset(), m_Hierachy, index };
}

ICS_API Indices::Indices(Indices::Hierachy hierachy)
	:
	m_Buffer(hierachy)
{
}


Indices::Indices(const Indices& rhs)
{
	*this = rhs;
}

const Indices& Indices::operator=(const Indices& rhs)
{
	m_Buffer = rhs.m_Buffer;
	return *this;
}

Indices::IndexBuffer::IndexBuffer(Hierachy& hierachy)
	:
	m_Hierachy(hierachy),
	m_TotalBufferedNodes(0u)
{
}