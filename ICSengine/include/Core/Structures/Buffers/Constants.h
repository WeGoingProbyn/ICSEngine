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

	private:
		darray<Element> m_Layout;
	};

public:
	Constants()
		:
		m_Layout(),
		m_BufferedConstants()
	{
	}
	Constants(Constants::Layout& layout)
		:
		m_Layout(layout),
		m_BufferedConstants(0u)
	{
	}

	template<typename T>
	void PushConstant(T constant);
	inline darray<char>& GetBuffer() { return m_ByteBlob; }

private:
	template<typename Dest, typename Src>
	void SetConstantInBuffer(char* ptr, Src constant)
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

private:
	darray<char> m_ByteBlob;
	Constants::Layout m_Layout;
	unsigned int m_BufferedConstants;
};

template<typename T>
void Constants::PushConstant(T constant)
{
	m_ByteBlob.Resize(m_ByteBlob.Size() + m_Layout[m_BufferedConstants].GetType());

	if constexpr (std::is_same<T, float>::value)
	{
		SetConstantInBuffer<float>(&m_ByteBlob[m_Layout[m_BufferedConstants].GetOffset()], constant);
	}
	else if constexpr (std::is_same<T, Vector<float, 4>>::value)
	{
		SetConstantInBuffer<Vector<float, 4>>(&m_ByteBlob[m_Layout[m_BufferedConstants].GetOffset()], constant);
	}
	else if constexpr (std::is_same<T, Matrix<float, 4>>::value)
	{
		SetConstantInBuffer<Matrix<float, 4>>(&m_ByteBlob[m_Layout[m_BufferedConstants].GetOffset()], constant);
	}
	else
	{
		ICS_ERROR("Constants: type miss match on push constant");
	}
};

