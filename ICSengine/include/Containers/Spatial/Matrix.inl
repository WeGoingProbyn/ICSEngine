#pragma once

#include "Containers/Spatial/Matrix.h"

template<typename T, unsigned int dim>
Matrix<T, dim>::Matrix()
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			if (row == column)
			{
				m_Data[row][column] = 1;
			}
			else
			{
				m_Data[row][column] = 0;
			}
		}
	}
}

template<typename T, unsigned int dim>
template<typename... Types>
Matrix<T, dim>::Matrix(Types... args)
{
	ICS_ASSERT_MSG(sizeof...(Types) > dim, "Matrix: Trying to construct matrix using more inputs than pointers in matrix");
	
	unsigned int row = 0;
	unsigned int column = 0;
	((m_Data[row == (dim - 1) ? 0u : row++][row == (dim - 1) ? column++ : column] = static_cast<T>(args)), ...);
}

template<typename T, unsigned int dim>
T& Matrix < T, dim>::operator [](unsigned int index)
{
	unsigned int row = index / dim;
	unsigned int col = index % dim;
	return m_Data[row][col];
}

template<typename T, unsigned int dim>
T& Matrix < T, dim>::operator ()(unsigned int row, unsigned int col)
{
	return m_Data[row][col];
}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::Transpose()
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			if (row != column)
			{
				tmp(row, column) = m_Data(column, row);
			}
		}
	}
	return tmp;
}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::Inverse()
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			if (!m_Data[row][column])
			{
				tmp(row, column) = 0;
			}
			else
			{
				tmp(row, column) = 1 / m_Data[row][column];
			}
		}
	}
	return tmp;
}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator-()
{
	Matrix<T, dim> tmp;
	for (unsigned int row; row < dim; row++)
	{
		for (unsigned int column; column < dim; column++)
		{
			tmp.m_Data[row][column] = -m_Data[row][column];
		}
	}
	return tmp;
}

/* ----------------------------- Scalar operating on a Matrix ----------------------------- */

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator +(T rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] + rhs;
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator +(const T& rhs)
//{
//	return this + rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator +=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] + rhs;
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator +=(const T& rhs)
//{
//	return this += rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator -(T rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] - rhs;
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator -(const T& rhs)
//{
//	return this - rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator -=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] - rhs;
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator -=(const T& rhs)
//{
//	return this -= rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator *(T rhs) {
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] * rhs;
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator *(const T& rhs)
//{
//	return this * rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator *=(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] * rhs;
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator *=(const T& rhs)
//{
//	return this *= rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator /(T rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] / rhs;
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator /(const T& rhs)
//{
//	return this / rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator /= (T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] / rhs;
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator /=(const T& rhs)
//{
//	return this /= rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator =(T rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = rhs;
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator =(const T& rhs)
//{
//	return this = rhs;
//}

/* ----------------------------- Matrix operating on a Matrix ----------------------------- */

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator +(Matrix<T, dim> rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] + rhs.m_Data[row][column];
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator +(const Matrix<T, dim>& rhs)
//{
//	return this + rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator +=(Matrix<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] + rhs.m_Data[row][column];
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator +=(const Matrix<T, dim>& rhs)
//{
//	return this += rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator -(Matrix<T, dim> rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] - rhs.GetData(row, column);
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator -(const Matrix<T, dim>& rhs)
//{
//	return this - rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator -=(Matrix<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] - rhs.GetData(row, column);
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator -=(const Matrix<T, dim>& rhs)
//{
//	return this -= rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator *(Matrix<T, dim> rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			T hold = 0;
			for (unsigned int index = 0; index < dim; index++)
			{
				hold += m_Data[row][index] * rhs.m_Data[index][column];
			}
			tmp.m_Data[row][column] = hold;
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator *(const Matrix<T, dim>& rhs)
//{
//	return this * rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator *=(Matrix<T, dim> rhs)
{
	//Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			T hold = 0;
			for (unsigned int index = 0; index < dim; index++)
			{
				hold += m_Data(row, index) * rhs.m_Data(index, column);
			}
			m_Data[row][column] = hold;
			//tmp.m_Data[row][column] = hold;
		}
	}
	//for (unsigned int row = 0; row < dim; row++) 
	//{
	//	for (unsigned int column = 0; column < dim; column++) 
	//	{
	//		m_Data[row][column] = tmp.GetData(row, column);
	//	}
	//}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator *=(const Matrix<T, dim>& rhs)
//{
//	return this *= rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim> Matrix<T, dim>::operator /(Matrix<T, dim> rhs)
{
	Matrix<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			tmp.m_Data[row][column] = m_Data[row][column] / rhs.m_Data[row][column];
		}
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim> Matrix<T, dim>::operator /(const Matrix<T, dim>& rhs)
//{
//	return this / rhs;
//}


template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator /=(Matrix<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = m_Data[row][column] / rhs.GetData(row, column);
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator /=(const Matrix<T, dim>& rhs)
//{
//	return this /= rhs;
//}

template<typename T, unsigned int dim>
Matrix<T, dim>& Matrix<T, dim>::operator =(Matrix<T, dim> rhs)
{
	for (unsigned int row = 0; row < dim; row++)
	{
		for (unsigned int column = 0; column < dim; column++)
		{
			m_Data[row][column] = rhs.m_Data[row][column];
		}
	}
	return *this;
}

//template<typename T, unsigned int dim>
//Matrix<T, dim>& Matrix<T, dim>::operator =(const Matrix<T, dim>& rhs)
//{
//	return this = rhs;
//}

/* ----------------------------- Vector operating on a Matrix ----------------------------- */

template<typename T, unsigned int dim>
Vector<T, dim> Matrix<T, dim>::operator *(Vector<T, dim> rhs) 
{
	T sum;
	Vector<T, dim> tmp;
	for (unsigned int row = 0; row < dim; row++) 
	{
		sum = 0;
		for (unsigned int column = 0; column < dim; column++) 
		{
			sum += m_Data[row][column] * rhs.m_Data[column];
		}
		tmp.m_Data[row] = sum;
	}
	return tmp;
}

//template<typename T, unsigned int dim>
//Vector<T, dim> Matrix<T, dim>::operator *(const Vector<T, dim>& rhs)
//{
//	return this * rhs;
//}