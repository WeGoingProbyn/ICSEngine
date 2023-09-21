#pragma once

#include "Containers/Spatial/Vector.h"
#include "Containers/Spatial/Matrix.h"

class Camera {
public:
	Camera();

	inline Vector<float, 3>& GetTarget() { return m_Target; }
	inline Vector<float, 3>& GetPosition() { return m_Position; }
	inline Vector<float, 3>& GetRightBasis() { return m_RightBasis; }
	inline Vector<float, 3>& GetUpwardBasis() { return m_UpwardBasis; }
	inline Vector<float, 3>& GetForwardBasis() { return m_ForwardBasis; }
	inline void SetTarget(Vector<float, 3> target) { m_Target = target; }
	inline void SetUpwardBasis(Vector<float, 3> up) { m_UpwardBasis = up; }
	inline void SetPosition(Vector<float, 3> position) { m_Position = position; }
	void RealignBasisVectors();
	
	//Matrix<float, 4>  TranslateCamera();
	//void RotateCamera(Vector<float, 2> rotation);
	//void CheckRotationInput(Vector<int, 2> mouseposition);
	//void CheckTranslationInput(bool* translation, float execute);
private:
	Vector<float, 3> m_Position;
	Vector<float, 3> m_Target;
	Vector<float, 3> m_ForwardBasis;
	Vector<float, 3> m_UpwardBasis;
	Vector<float, 3> m_RightBasis;

	Vector<float, 2> m_YawPitch;
	Vector<int, 2> m_LastKnownPosition;
};