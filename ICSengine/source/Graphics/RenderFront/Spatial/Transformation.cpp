#include "Graphics/RenderFront/Spatial/Transformation.h"

Transformation::Transformation() {}

void Transformation::SetScale(Vector<float, 3> actor) { m_Scale = actor; }

void Transformation::SetRotation(Vector<float, 3> actor) {
	m_Rotation = actor;
	//convert to radians
	m_Rotation *= (3.14159f / 180.0f);
}

void Transformation::SetTranslation(Vector<float, 3> actor) { m_Translation = actor; }

Matrix<float, 4> Transformation::ScaleVector() {
	return Matrix<float, 4>(m_Scale[0], 0.0f, 0.0f, 0.0f,
							0.0f, m_Scale[1], 0.0f, 0.0f,
							0.0f, 0.0f, m_Scale[2], 0.0f,
							0.0f, 0.0f,		  0.0f, 1.0f);
}

Matrix<float, 4> Transformation::TranslateVector() {
	Matrix<float, 4> translate;

	translate(3, 0) = m_Translation(0);
	translate(3, 1) = m_Translation(1);
	translate(3, 2) = m_Translation(2);
	return translate;
}

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
}

Matrix<float, 4> Transformation::Transform() {
	return  (TranslateVector() * RotateWithEuler() * ScaleVector());
}

Matrix<float, 4> Transformation::TransformNoTranslation() {
	return ScaleVector() * RotateWithEuler();
}

