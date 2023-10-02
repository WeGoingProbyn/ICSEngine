#include "Core/Structures/Buffers/Constants.h"

Constants::Set::Set(char* ptr, Constants::Layout& layout)
	:
	m_Ptr(ptr),
	m_Layout(layout)
{
}

Constants::ConstantBuffer::ConstantBuffer(Layout layout)
	:
	m_Layout(layout),
	m_ByteBlob(MemoryType::ICS_MODEL)
{
}

Constants::ConstantBuffer::ConstantBuffer()
	:
	m_ByteBlob(MemoryType::ICS_MODEL)
{
}

Constants::Set Constants::ConstantBuffer::End()
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Constants: Buffer is nullptr, cannot return on End");
	return Set{ &m_ByteBlob[0] + m_ByteBlob.Size() - m_Layout.Size(), m_Layout };
}

Constants::Set Constants::ConstantBuffer::Begin()
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on Begin");
	return Set{ &m_ByteBlob[0], m_Layout };
}

Constants::Set Constants::ConstantBuffer::operator[](unsigned index)
{
	ICS_ASSERT_MSG(m_ByteBlob.Size() > 0, "Vertices: Buffer is nullptr, cannot return on operator[]");
	return Set{ &m_ByteBlob[0] + m_Layout.Size() * index, m_Layout };
}

Constants::Constants(const Constants& rhs)
{
	*this = rhs;
}

const Constants& Constants::operator=(const Constants& rhs)
{
	m_Buffer = rhs.m_Buffer;
	return *this;
}