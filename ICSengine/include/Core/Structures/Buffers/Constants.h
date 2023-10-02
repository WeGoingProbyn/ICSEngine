#pragma once

#include "Containers/array/darray.h"
#include "Containers/Spatial/Vector.h"
#include "Containers/Spatial/Matrix.h"

class Constants
{
public:
	enum Types
	{
		SCALAR = sizeof(float),
		VECTOR = sizeof(Vector<float, 4>),
		MATRIX = sizeof(Matrix<float, 4>)
	};

	class Layout
	{
	public:
		class Element
		{
		public:
			Element() : m_Type(Constants::Types::SCALAR), m_Offset(0u) {}
			Element(Constants::Types type, unsigned int offset)
				:
				m_Type(type),
				m_Offset(offset)
			{
			}

			inline unsigned int GetType() { return m_Type; }
			inline unsigned int GetOffset() { return m_Offset; }
			inline unsigned int GetEndOfElement() { return m_Offset + m_Type; }
		private:
			unsigned int m_Offset;
			Constants::Types m_Type;
		};
	public:
		template<typename... Args>
		inline Layout(Args... args)
		{
			(PushType(args), ...);
		}

		inline void PushType(Constants::Types type)
		{
			if (m_Layout.Size() > 0)
			{
				m_Layout.PushToEnd({ type, m_Layout[m_Layout.Last()].GetOffset() });
			}
			else
			{
				m_Layout.PushToEnd({ type, 0u });
			}
		}

		inline Constants::Layout::Element operator[](unsigned int index)
		{
			return m_Layout[index];
		}

		inline darray<Element>& GetLayout() { return m_Layout; }
		inline unsigned int Size()
		{
			return m_Layout.Size() > 0 ? m_Layout[m_Layout.Last()].GetEndOfElement() : 0u;
		}
	private:
		darray<Element> m_Layout;
	};

public:
	class Set
	{
		friend class ConstantBuffer;
	public:
		Set(char* ptr, Constants::Layout& layout);

		template<typename T>
		void PushConstants(unsigned int index, T&& value);
		template<typename First, typename... Rest>
		void PushConstants(unsigned int index, First&& first, Rest&&... rest);

		inline Constants::Layout& GetLayout() { return m_Layout; }
		inline char* GetRawPointer() { return m_Ptr; }

	private:
		template<typename Dest, typename Src>
		void SetInBuffer(char* ptr, Src&& value);
	private:
		char* m_Ptr;
		Constants::Layout& m_Layout;
	};

public:
	class ConstantBuffer
	{
	public:
		ICS_API ConstantBuffer();
		ICS_API ConstantBuffer(Constants::Layout layout);

		inline Constants::Layout& GetLayout() { return m_Layout; }
		inline char* GetBufferPointer() { return &m_ByteBlob[0]; }
		inline unsigned int GetNumberOfSets() { return m_ByteBlob.Size() / m_Layout.Size(); }
		inline void Flush() { m_ByteBlob.Flush(); }

		template<typename... objs>
		void PushSet(objs&&... args);

		ICS_API Set End();
		ICS_API Set Begin();
		ICS_API Set operator[](unsigned int index);
	private:
		darray<char> m_ByteBlob;
		Constants::Layout m_Layout;
	};

public:
	Constants()
		:
		m_Buffer()
	{
	}
	Constants(Constants::Layout layout)
		:
		m_Buffer(layout)
	{
	}

	ICS_API Constants(const Constants& rhs);
	ICS_API const Constants& operator=(const Constants& rhs);

	inline unsigned int GetNumberOfSets() { return m_Buffer.GetNumberOfSets(); }
	inline ConstantBuffer& GetBuffer() { return m_Buffer; }
	inline Layout& GetLayout() { return m_Buffer.GetLayout(); }

	template<typename... Types>
	void PushConstantSet(Types&&... args) 
	{ 
		m_Buffer.PushSet(args...);
	}
private:
	ConstantBuffer m_Buffer;
};

template<typename... objs>
void Constants::ConstantBuffer::PushSet(objs&&... args)
{
	m_ByteBlob.Resize(m_ByteBlob.Size() + m_Layout.Size());
	End().PushConstants(0u, std::forward<objs>(args)...);
}

template<typename First, typename... Rest>
void Constants::Set::PushConstants(unsigned int index, First&& first, Rest&&... rest)
{
	PushConstants(index, std::forward<First>(first));
	PushConstants(index + 1, std::forward<Rest>(rest)...);
}

template<typename T>
void Constants::Set::PushConstants(unsigned int index, T&& value)
{
	Constants::Layout::Element element = m_Layout[index];
	char* attribute = m_Ptr + element.GetOffset();

	if constexpr (std::is_same<std::remove_reference_t<decltype(value)>, float>::value)
	{
		SetInBuffer<float>(attribute, std::forward<T>(value));
	}
	else if constexpr (std::is_same<std::remove_reference_t<decltype(value)>, Vector<float, 4>>::value)
	{
		SetInBuffer<Vector<float, 4>>(attribute, std::forward<T>(value));
	}
	else if constexpr (std::is_same<std::remove_reference_t<decltype(value)>, Matrix<float, 4>>::value)
	{
		SetInBuffer<Matrix<float, 4>>(attribute, std::forward<T>(value));
	}
	else
	{
		ICS_ERROR("Constants: type miss match on push constant");
	}
};

template<typename Dest, typename Src>
void Constants::Set::SetInBuffer(char* ptr, Src&& constant)
{
	if constexpr (std::is_same<Dest, float>::value)
	{
		*reinterpret_cast<Dest*>(ptr) = constant;
	}
	else if constexpr (std::is_assignable<Dest, Src>::value)
	{
		for (unsigned int index = 0; index < sizeof(constant) / sizeof(float); index++)
		{
			*reinterpret_cast<float*>(ptr + (index * sizeof(float))) = constant[index];
		}
	}
	else
	{
		ICS_ERROR("Constants: Type mismatch during attribute assignment");
	}
}

