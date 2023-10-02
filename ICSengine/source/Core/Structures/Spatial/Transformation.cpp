#include "Core/Structures/Spatial/Transformation.h"

Transformation::Transformation()
{
}

void Transformation::SetScale(Vector<float, 3> actor) 
{
	m_Scale = actor;
}

void Transformation::SetRotation(Vector<float, 3> actor)
{
	m_Rotation = actor;
	//convert to radians
	m_Rotation *= (3.14159f / 180.0f);
}

void Transformation::SetTranslation(Vector<float, 3> actor) 
{
	m_Translation = actor;
}

Matrix<float, 4> Transformation::ScaleVector() {
	Matrix<float, 4> scale;
	scale(0, 0) = m_Scale[0];
	scale(1, 1) = m_Scale[1];
	scale(2, 2) = m_Scale[2];
	return scale;
};

Matrix<float, 4> Transformation::TranslateVector() {
	Matrix<float, 4> translate;

	translate(3, 0) = m_Translation[0];
	translate(3, 1) = m_Translation[1];
	translate(3, 2) = m_Translation[2];
	return translate;
};

Matrix<float, 4> Transformation::RotateWithEuler() {
	Matrix<float, 4> rotation_x;
	Matrix<float, 4> rotation_y;
	Matrix<float, 4> rotation_z;

	rotation_x(1, 1) = std::cos(m_Rotation(0));
	rotation_x(1, 2) = -std::sin(m_Rotation(0));
	rotation_x(2, 1) = std::sin(m_Rotation(0));
	rotation_x(2, 2) = std::cos(m_Rotation(0));

	rotation_y(0, 0) = std::cos(m_Rotation(1));
	rotation_y(0, 2) = std::sin(m_Rotation(1));
	rotation_y(2, 0) = -std::sin(m_Rotation(1));
	rotation_y(2, 2) = std::cos(m_Rotation(1));

	rotation_z(0, 0) = std::cos(m_Rotation(2));
	rotation_z(0, 1) = -std::sin(m_Rotation(2));
	rotation_z(1, 0) = std::sin(m_Rotation(2));
	rotation_z(1, 1) = std::cos(m_Rotation(2));

	return rotation_x * rotation_y * rotation_z;
};

Matrix<float, 4> Transformation::Transform() {
	m_Transform = (ScaleVector() * RotateWithEuler() * TranslateVector());
	return m_Transform;
};

Matrix<float, 4> Transformation::TransformNoTranslation() {
	return ScaleVector() * RotateWithEuler();
};

Transformation Transformation::operator +(const Transformation& rhs)
{
	Transformation tmp;
	tmp.SetScale(m_Scale + rhs.m_Scale);
	tmp.SetRotation(m_Rotation + rhs.m_Rotation);
	tmp.SetTranslation(m_Translation + rhs.m_Translation);
	return tmp;
};

Transformation Transformation::operator -(const Transformation& rhs)
{
	Transformation tmp;
	tmp.SetScale(m_Scale - rhs.m_Scale);
	tmp.SetRotation(m_Rotation - rhs.m_Rotation);
	tmp.SetTranslation(m_Translation - rhs.m_Translation);
	return tmp;
};

Transformation Transformation::operator /(const Transformation& rhs)
{
	Transformation tmp;
	tmp.SetScale(m_Scale / rhs.m_Scale);
	tmp.SetRotation(m_Rotation / rhs.m_Rotation);
	tmp.SetTranslation(m_Translation / rhs.m_Translation);
	return tmp;
};

Transformation Transformation::operator *(const Transformation& rhs)
{
	Transformation tmp;
	tmp.SetScale(m_Scale * rhs.m_Scale);
	tmp.SetRotation(m_Rotation * rhs.m_Rotation);
	tmp.SetTranslation(m_Translation * rhs.m_Translation);
	return tmp;
};

Transformation& Transformation::operator +=(const Transformation& rhs)
{
	m_Scale += rhs.m_Scale;
	m_Rotation += rhs.m_Rotation;
	m_Translation += rhs.m_Translation;
	return *this;
};

Transformation& Transformation::operator -=(const Transformation& rhs)
{
	m_Scale -= rhs.m_Scale;
	m_Rotation -= rhs.m_Rotation;
	m_Translation -= rhs.m_Translation;
	return *this;
};

Transformation& Transformation::operator /=(const Transformation& rhs)
{
	m_Scale /= rhs.m_Scale;
	m_Rotation /= rhs.m_Rotation;
	m_Translation /= rhs.m_Translation;
	return *this;
};

Transformation& Transformation::operator *=(const Transformation& rhs)
{
	m_Scale *= rhs.m_Scale;
	m_Rotation *= rhs.m_Rotation;
	m_Translation *= rhs.m_Translation;
	return *this;
};
