#pragma once

#include "Containers/array/darray.h"
#include "Containers/String/String.h"

class Shaders
{
public:
	enum Types
	{
		PIXEL,
		VERTEX,
		GEOMETRY,
		TESSELATION_HULL,
		TESSELATION_DOMAIN
	};

public:
	class Layout
	{
	public:
		class Element
		{
		public:
			Element() {}
			Element(Types type, unsigned int offset) : m_Type(type) {}
		private:
			Types m_Type;
		};
	
	private:
		darray<Element> m_Structure;
	};

public:
	class Shader
	{
		friend class ShaderBuffer;
	public:
		Shader();
	
	private:
		char* m_Ptr;
		Layout& m_Layout;
	};

public:
	class ShaderBuffer
	{
	public:
		ShaderBuffer();
	
	private:
		Layout m_Layout;
		darray<String> m_ByteBlob;
	};
};