#pragma once

#include <cmath>

#include "Defines.h"
#include "Core/Debugger/Logger.h"

template<typename T, unsigned int dim>
class Vector
{
public:
	class Iterator {
	public:
		Iterator(Vector<T, dim>& arr, unsigned int start = 0) : vecRef(arr), index(start) {}

		// Define iterator operations
		void operator++() { index++; }
		T& operator*() { return vecRef[index]; }
		bool operator!=(const Iterator& other) const { return index != other.index; }
	private:
		Vector<T, dim>& vecRef;
		unsigned int index;
	};

	// Functions to get iterators
	Iterator begin() {
		return Iterator(*this);
	}

	Iterator end() {
		return Iterator(*this, dim);
	}
public:
	Vector();
	template<typename... Types>
	Vector(Types... args);

	T* C_Arr();
	const T* C_Arr() const;
	Vector<T, dim> operator -();
	T& operator ()(unsigned int index);
	T& operator [](unsigned int index);
	bool operator != (const Vector<T, dim>& rhs) const;
	bool operator == (const Vector<T, dim>& rhs) const;

	T Magnitude();
	Vector<T, dim> Reverse();
	T DotProduct(const Vector<T, dim>& rhs);

	Vector<T, dim> Normalise();
	Vector<T, dim> CrossProduct(const Vector<T, dim>& rhs);

	Vector<T, dim> operator +(T rhs);
	Vector<T, dim> operator -(T rhs);
	Vector<T, dim> operator *(T rhs);
	Vector<T, dim> operator /(T rhs);

	Vector<T, dim>& operator +=(T rhs);
	Vector<T, dim>& operator -=(T rhs);
	Vector<T, dim>& operator *=(T rhs);
	Vector<T, dim>& operator /=(T rhs);

	Vector<T, dim> operator +(Vector<T, dim> rhs);
	Vector<T, dim> operator -(Vector<T, dim> rhs);
	Vector<T, dim> operator *(Vector<T, dim> rhs);
	Vector<T, dim> operator /(Vector<T, dim> rhs);

	Vector<T, dim>& operator += (Vector<T, dim> rhs);
	Vector<T, dim>& operator -= (Vector<T, dim> rhs);
	Vector<T, dim>& operator *= (Vector<T, dim> rhs);
	Vector<T, dim>& operator /= (Vector<T, dim> rhs);

	Vector<T, dim>& operator =(T rhs);
	Vector<T, dim>& operator =(Vector<T, dim> rhs);
private:
	T m_Data[dim];

};

#include "Vector.inl"


