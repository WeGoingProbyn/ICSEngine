#pragma once

#include "Containers/Spatial/Vector.h"

template<typename T, unsigned int dim>
Vector<T, dim>::Vector()
{
	for (unsigned int i = 0; i < dim; i++)
	{
		m_Data[i] = 0;
	}
}

template<typename T, unsigned int dim>
template<typename... Types>
Vector<T, dim>::Vector(Types... args)
{
	if (sizeof...(Types) > dim)
	{
		ICS_WARN("Vector: Trying to construct vector using more values than space in vector, values clipped to fit")
	}

	unsigned int index = 0;
	((m_Data[index == dim ? index : index++] = static_cast<T>(args)), ...);
}

template<typename T, unsigned int dim>
T& Vector<T, dim>::operator ()(unsigned int index)
{
	return m_Data[index];
}

template<typename T, unsigned int dim>
T& Vector<T, dim>::operator [](unsigned int index)
{
	return m_Data[index];
}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator =(Vector<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = rhs.m_Data[row];
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator =(const Vector<T, dim>& rhs)
//{
//	return this = rhs;
//}

template<typename T, unsigned int dim>
bool Vector<T, dim>::operator ==(const Vector<T, dim>& rhs) const
{
	for (unsigned int index = 0; index < dim; index++)
	{
		if (rhs.m_Data[index] != m_Data[index])
		{
			return false;
		}
	}
	return true;
}

template<typename T, unsigned int dim>
bool Vector<T, dim>::operator !=(const Vector<T, dim>& rhs) const
{
	for (unsigned int index = 0; index < dim; index++)
	{
		if (rhs.m_Data[index] == m_Data[index])
		{
			return false;
		}
	}
	return true;
}

template<typename T, unsigned int dim>
const T* Vector<T, dim>::C_Arr() const {
	return m_Data;
}

template<typename T, unsigned int dim>
T* Vector<T, dim>::C_Arr() {
	return m_Data;
}

/* ----------------------------- Vector Operations ----------------------------- */

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::CrossProduct(Vector<T, dim> rhs) {
//	Vector<T, dim> tmp;
//	if (dim != 3) {
//		ICS_ERROR("Maths: A vector in a cross product calcuation does not have 3 dimensions!");
//		return tmp;
//	}
//	tmp.m_Data[0] = (m_Data[1] * rhs.m_Data[2]) - (m_Data[2] * rhs.m_Data[1]);
//	tmp.m_Data[1] = (m_Data[2] * rhs.m_Data[0]) - (m_Data[0] * rhs.m_Data[2]);
//	tmp.m_Data[2] = (m_Data[0] * rhs.m_Data[1]) - (m_Data[1] * rhs.m_Data[0]);
//	return tmp;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::CrossProduct(const Vector<T, dim>& rhs) {
	Vector<T, dim> tmp;
	if (dim != 3) {
		ICS_ERROR("Maths: A vector in a cross product calcuation does not have 3 dimensions!");
		return tmp;
	}
	tmp.m_Data[0] = (m_Data[1] * rhs.m_Data[2]) - (m_Data[2] * rhs.m_Data[1]);
	tmp.m_Data[1] = (m_Data[2] * rhs.m_Data[0]) - (m_Data[0] * rhs.m_Data[2]);
	tmp.m_Data[2] = (m_Data[0] * rhs.m_Data[1]) - (m_Data[1] * rhs.m_Data[0]);
	return tmp;
}

//template<typename T, unsigned int dim>
//T Vector<T, dim>::DotProduct(Vector<T, dim> rhs)
//{
//	T tmp = 0;
//	for (unsigned int row = 0; row < dim; row++)
//	{
//		tmp += m_Data[row] * rhs.m_Data[row];
//	}
//	return tmp;
//}

template<typename T, unsigned int dim>
T Vector<T, dim>::DotProduct(const Vector<T, dim>& rhs)
{
	T tmp = 0;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp += m_Data[row] * rhs.m_Data[row];
	}
	return tmp;
}

template<typename T, unsigned int dim>
T Vector<T, dim>::Magnitude()
{
	T tmp = 0;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp += m_Data[row] * m_Data[row];
	}
	return std::pow(tmp, 0.5f);
}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::Normalise()
{
	return *this * (1 / Magnitude());
}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator -()
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = -m_Data[row];
	}
	return tmp;
}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::Reverse()
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp[dim - 1 - row] = m_Data[row];
	}
	return tmp;
}

/* ----------------------------- Scalar operating on a Vector ----------------------------- */

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator +(T rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] + rhs;
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator +(const T& rhs)
//{
//	return this + rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator +=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] + rhs;
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator +=(const T& rhs)
//{
//	return this += rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator -(T rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] + rhs;
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator -(const T& rhs)
//{
//	return this - rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator -=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] - rhs;
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator -=(const T& rhs)
//{
//	return this -= rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator *(T rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] * rhs;
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator *(const T& rhs)
//{
//	return this * rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator *=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] * rhs;
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator *=(const T& rhs)
//{
//	return this *= rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator /(T rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] / rhs;
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator /(const T& rhs)
//{
//	return this / rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator /=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] / rhs;
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator /=(const T& rhs)
//{
//	return this /= rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator =(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = rhs;
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator =(const T& rhs)
//{
//	return this = rhs;
//}

/* ----------------------------- Vector operating on a Vector ----------------------------- */

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator +(Vector<T, dim> rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] + rhs.m_Data[row];
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator +(const Vector<T, dim>& rhs)
//{
//	return this + rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator +=(Vector<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] + rhs.m_Data[row];
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator +=(const Vector<T, dim>& rhs)
//{
//	return this += rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator -(Vector<T, dim> rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] - rhs.m_Data[row];
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator -(const Vector<T, dim>& rhs)
//{
//	return this - rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator -=(Vector<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] - rhs.m_Data[row];
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator -=(const Vector<T, dim>& rhs)
//{
//	return this -= rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator *(Vector<T, dim> rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] * rhs.m_Data[row];
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator *(const Vector<T, dim>& rhs)
//{
//	return this * rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator *=(Vector<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] * rhs.m_Data[row];
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator *=(const Vector<T, dim>& rhs)
//{
//	return this *= rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim> Vector<T, dim>::operator /(Vector<T, dim> rhs)
{
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		tmp.m_Data[row] = m_Data[row] / rhs.m_Data[row];
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Vector<T, dim>::operator /(const Vector<T, dim>& rhs)
//{
//	return this / rhs;
//}

template<typename T, unsigned int dim>
Vector<T, dim>& Vector<T, dim>::operator /=(Vector<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		m_Data[row] = m_Data[row] / rhs.m_Data[row];
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Vector<T, dim>& Vector<T, dim>::operator /=(const Vector<T, dim>& rhs)
//{
//	return this /= rhs;
//}