#pragma once

#include "Containers/array/darray.h"
#include "Containers/String/String.h"
#include "Core/Structures/Buffers/Constants.h"

class Shaders
{
public:
	enum Platform
	{
		OPENGL,
		VULKAN,
		DIRECTX,
		UNKOWN_PLATFORM
	};

	enum Types
	{
		PIXEL,
		VERTEX,
		GEOMETRY,
		TESSELATION_HULL,
		TESSELATION_DOMAIN,
		UNKOWN_SHADER
	};

public:
	class Layout
	{
	public:
		class Element
		{
		public:
			Element() 
				:
				m_ID(0u),
				m_Type(Types::UNKOWN_SHADER)
			{
			}

			Element(unsigned int id, Types type) 
				:
				m_ID(id),
				m_Type(type)
			{
			}

			inline unsigned int GetID() { return m_ID; }
			inline Shaders::Types GetType() { return m_Type; }
			// TODO: If the type of shader being pushed does not match
			//		the layout then can try and traverse the string to find
			//		indicators on what type of shader is being added....
			//		this will be easier to do after the platform check has
			//		has been completed. Things like VSin or PSin in HLSL are good indicators

		private:
			Types m_Type;
			unsigned int m_ID;
		};
	
	public:
		Layout() 
			: 
			m_Structure(MemoryType::ICS_SHADER),
			m_Platform(Platform::UNKOWN_PLATFORM) {}

		template<typename... Args>
		Layout(Shaders::Platform platform_type, Args... shader_types);

		void SetShaderPlatform(Platform platform) { m_Platform = platform; }
		void PushShaderType(Types type) { m_Structure.PushToEnd({ m_Structure.Size(), type }); }

		inline darray<Element>& GetStructure() { return m_Structure; }

		// TODO: If Platform is not set by the user, can try and check the loaded strings
		//		for certain key words which are contained within the different languages
		//		eg for HLSL (DirectX) words like cbuffer and vsin or psin etc....

	private:
		Platform m_Platform;
		darray<Element> m_Structure;
	};

public:
	class Shader
	{
		friend class ShaderBuffer;
	public:
		Shader(String& str, Layout& layout)
			:
			m_String(str),
			m_Layout(layout) {}

		inline String& GetShaderString() { return m_String; }
	
	private:
		String& m_String;
		Layout& m_Layout;
	};

public:
	class ShaderBuffer
	{
	public:
		ShaderBuffer()
			:
			m_ByteBlob(MemoryType::ICS_SHADER)
		{
		}
		ShaderBuffer(Layout& layout) 
			: 
			m_Layout(layout),
			m_ByteBlob(MemoryType::ICS_SHADER) 
		{
		}
	
		inline Layout& GetShaderLayout() { return m_Layout; }

		ICS_API inline Shader Begin() { return Shader(m_ByteBlob[0], m_Layout); }
		ICS_API inline Shader End() { return Shader(m_ByteBlob[m_ByteBlob.Last()], m_Layout); }
		inline Shader operator[](unsigned int index) { return Shader(m_ByteBlob[index], m_Layout); }

		//ICS_API void PushShaderToBuffer(String str);
		ICS_API void PushShaderToBuffer(String& str);
	private:
		Layout m_Layout;
		darray<String> m_ByteBlob;
	};

public:
	Shaders() {}
	Shaders(Layout& layout, Constants::Layout& const_layout)
		:
		m_Buffer(layout),
		m_Constants(const_layout)
	{
	}

	template<typename... Args>
	inline void PushConstants(Args... args);

	inline void PushSource(String str) { return m_Buffer.PushShaderToBuffer(str); }
	inline ShaderBuffer& GetBuffer() { return m_Buffer; }
	inline Constants& GetConstants() { return m_Constants; }
	inline Layout& GetLayout() { return m_Buffer.GetShaderLayout(); }
	inline void FlushConstants() { m_Constants.GetBuffer().Flush(); }
private:
	Constants m_Constants;
	ShaderBuffer m_Buffer;
};

template<typename... Args>
Shaders::Layout::Layout(Shaders::Platform platform_type, Args... shader_types)
	:
	m_Platform(platform_type)
{
	(PushShaderType(shader_types), ...);
};

template<typename... Args>
void Shaders::PushConstants(Args... args)
{
	m_Constants.PushConstantSet(args...);
};

