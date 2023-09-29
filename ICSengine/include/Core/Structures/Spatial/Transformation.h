#pragma once

#include "Containers/Spatial/Vector.h"
#include "Containers/Spatial/Matrix.h"

class Transformation {
public:
	ICS_API Transformation();

	ICS_API void SetScale(Vector<float, 3> actor);
	ICS_API void SetRotation(Vector<float, 3> actor);
	ICS_API void SetTranslation(Vector<float, 3> actor);

	inline Vector<float, 3>& GetScaleVector() { return m_Scale; }
	inline Vector<float, 3>& GetRotationVector() { return m_Rotation; }
	inline Vector<float, 3>& GetTranslationVector() { return m_Translation; }

	ICS_API Matrix<float, 4> ScaleVector();
	ICS_API Matrix<float, 4> RotateWithEuler();
	ICS_API Matrix<float, 4> TranslateVector();
	ICS_API Matrix<float, 4> Transform();
	ICS_API Matrix<float, 4> TransformNoTranslation();
private:
	Vector<float, 3> m_Scale;
	Vector<float, 3> m_Rotation;
	Vector<float, 3> m_Translation;
};