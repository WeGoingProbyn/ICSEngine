#pragma once

#include "Containers/Spatial/Vector.h"

template<typename T, unsigned int dim>
class Matrix
{
public:
	Matrix();
	template<typename... Types>
	Matrix(Types... args);
	Matrix<T, dim> Transpose();
	Matrix<T, dim> Inverse();

	Matrix<T, dim> operator -();
	T& operator [](unsigned int index);
	T& operator ()(unsigned int row, unsigned int col);

	Matrix<T, dim>& operator =(T rhs);
	//Matrix<T, dim>& operator =(const T& rhs);
	Matrix<T, dim>& operator =(Matrix<T, dim> rhs);
	//Matrix<T, dim>& operator =(const Matrix<T, dim>& rhs);

	Matrix<T, dim> operator -(T rhs);
	Matrix<T, dim> operator *(T rhs);
	Matrix<T, dim> operator +(T rhs);
	Matrix<T, dim> operator /(T rhs);
	//Matrix<T, dim> operator -(const T& rhs);
	//Matrix<T, dim> operator *(const T& rhs);
	//Matrix<T, dim> operator +(const T& rhs);
	//Matrix<T, dim> operator /(const T& rhs);

	Matrix<T, dim>& operator +=(T rhs);
	Matrix<T, dim>& operator -=(T rhs);
	Matrix<T, dim>& operator *=(T rhs);
	Matrix<T, dim>& operator /=(T rhs);
	//Matrix<T, dim>& operator +=(const T& rhs);
	//Matrix<T, dim>& operator -=(const T& rhs);
	//Matrix<T, dim>& operator *=(const T& rhs);
	//Matrix<T, dim>& operator /=(const T& rhs);

	Matrix<T, dim> operator +(Matrix<T, dim> rhs);
	Matrix<T, dim> operator -(Matrix<T, dim> rhs);
	Matrix<T, dim> operator *(Matrix<T, dim> rhs);
	Matrix<T, dim> operator /(Matrix<T, dim> rhs);
	//Matrix<T, dim> operator +(const Matrix<T, dim>& rhs);
	//Matrix<T, dim> operator -(const Matrix<T, dim>& rhs);
	//Matrix<T, dim> operator *(const Matrix<T, dim>& rhs);
	//Matrix<T, dim> operator /(const Matrix<T, dim>& rhs);

	Matrix<T, dim>& operator +=(Matrix<T, dim> rhs);
	Matrix<T, dim>& operator -=(Matrix<T, dim> rhs);
	Matrix<T, dim>& operator *=(Matrix<T, dim> rhs);
	Matrix<T, dim>& operator /=(Matrix<T, dim> rhs);
	//Matrix<T, dim>& operator +=(const Matrix<T, dim>& rhs);
	//Matrix<T, dim>& operator -=(const Matrix<T, dim>& rhs);
	//Matrix<T, dim>& operator *=(const Matrix<T, dim>& rhs);
	//Matrix<T, dim>& operator /=(const Matrix<T, dim>& rhs);


	Vector<T, dim> operator *(Vector<T, dim> rhs);
	//Vector<T, dim> operator *(const Vector<T, dim>& rhs);

private:
	T m_Data[dim][dim];
};

#include "Matrix.inl"


