#include "Core/Structures/Buffers/Shaders.h"

void Shaders::ShaderBuffer::PushShaderToBuffer(String& str)
{
	m_ByteBlob.PushToEnd(str);
}
