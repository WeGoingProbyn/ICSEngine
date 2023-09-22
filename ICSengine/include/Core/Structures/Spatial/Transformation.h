#pragma once

#include "Containers/Spatial/Vector.h"
#include "Containers/Spatial/Matrix.h"

class Transformation {
public:
	ICS_API Transformation();

	void SetScale(Vector<float, 3> actor);
	void SetRotation(Vector<float, 3> actor);
	void SetTranslation(Vector<float, 3> actor);

	inline Vector<float, 3>& GetScaleVector() { return m_Scale; }
	inline Vector<float, 3>& GetRotationVector() { return m_Rotation; }
	inline Vector<float, 3>& GetTranslationVector() { return m_Translation; }

	Matrix<float, 4> ScaleVector();
	Matrix<float, 4> RotateWithEuler();
	Matrix<float, 4> TranslateVector();

	Matrix<float, 4> Transform();
	Matrix<float, 4> TransformNoTranslation();
private:
	Vector<float, 3> m_Scale;
	Vector<float, 3> m_Rotation;
	Vector<float, 3> m_Translation;
};