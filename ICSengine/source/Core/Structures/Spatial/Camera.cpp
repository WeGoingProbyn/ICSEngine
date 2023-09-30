#include "Core/Structures/Spatial/Camera.h"

Camera::Camera()
{
	m_Position = Vector<float, 3>(0.0f, 0.0f, 10.0f);
	m_Target = Vector<float, 3>(0.0f, 0.0f, 0.0f);
	m_UpwardBasis = Vector<float, 3>(0.0f, 1.0f, 0.0f);
	m_ForwardBasis = (m_Position - m_Target).Normalise();
	RealignBasisVectors();
}

void Camera::RealignBasisVectors()
{
	m_RightBasis = m_ForwardBasis.CrossProduct(m_UpwardBasis).Normalise();
	m_UpwardBasis = m_RightBasis.CrossProduct(m_ForwardBasis).Normalise();
}


//void Camera::CheckTranslationInput(bool* translation, float execute) {
//	// Forwards, Backwards, Right, Left, Up, Down
//	for (int index = 0; index < 6; index++) {
//		if (!translation[index]) {
//			continue;
//		}
//		else {
//			float speed = 2.0f;
//			switch (index)
//			{
//			case(0):
//				m_Position += m_ForwardBasis * speed * execute;
//				break;
//			case(1):
//				m_Position -= m_ForwardBasis * speed * execute;
//				break;
//			case(2):
//				m_Position += m_RightBasis * speed * execute;
//				break;
//			case(3):
//				m_Position -= m_RightBasis * speed * execute;
//				break;
//			case(4):
//				m_Position += m_ForwardBasis.CrossProduct(m_RightBasis).Normalise() * speed * execute;
//				break;
//			case(5):
//				m_Position -= m_ForwardBasis.CrossProduct(m_RightBasis).Normalise() * speed * execute;
//				break;
//			}
//		}
//	}
//}
// 
Matrix<float, 4> Camera::Translate() {
	Matrix<float, 4> CameraVectors;
	Matrix<float, 4> CameraPosition;

	CameraVectors(0, 0) = m_RightBasis[0];
	CameraVectors(0, 1) = m_RightBasis[1];
	CameraVectors(0, 2) = m_RightBasis[2];

	CameraVectors(1, 0) = m_UpwardBasis[0];
	CameraVectors(1, 1) = m_UpwardBasis[1];
	CameraVectors(1, 2) = m_UpwardBasis[2];

	CameraVectors(2, 0) = m_ForwardBasis[0];
	CameraVectors(2, 1) = m_ForwardBasis[1];
	CameraVectors(2, 2) = m_ForwardBasis[2];

	CameraPosition(3, 0) = -m_Position[0];
	CameraPosition(3, 1) = -m_Position[1];
	CameraPosition(3, 2) = -m_Position[2];

	return (CameraPosition * CameraVectors);
}

//void Camera::CheckRotationInput(Vector<int, 2> mouseposition) {
//	if (mouseposition == m_LastKnownPosition) { ; }
//	else {
//		m_LastKnownPosition = mouseposition;
//
//		float sensitivity = 0.1f;
//		Vector<float, 2> floatposition = { (float)mouseposition(0), (float)mouseposition(1) };
//		floatposition(0) *= sensitivity;
//		floatposition(1) *= sensitivity;
//		RotateCamera(floatposition);
//	}
//}
//
//void Camera::RotateCamera(Vector<float, 2> rotation)
//{
//	m_YawPitch(0) = rotation(0);
//	m_YawPitch(1) = rotation(1);
//
//	if (m_YawPitch(1) > 89.0f) { m_YawPitch(1) = 89.0f; }
//	if (m_YawPitch(1) < -89.0f) { m_YawPitch(1) = -89.0f; }
//
//	float radians = 3.1415f / 180.0f;
//	m_ForwardBasis(0) = cos(m_YawPitch(0) * radians) * cos(m_YawPitch(1) * radians);
//	m_ForwardBasis(1) = sin(m_YawPitch(1) * radians);
//	m_ForwardBasis(2) = sin(m_YawPitch(0) * radians) * cos(m_YawPitch(1) * radians);
//	m_ForwardBasis.Normalise();
//	RealignBasisVectors();
//}
//
//void Camera::BuildCameraToUI() {
//	static bool islocked = false;
//	static Vector<float, 2> rotation = { 90.0f, 0.0f };
//	bool translation[6];
//
//	ImGui::Text("Camera Orientation: ");
//	ImGui::SliderFloat("Camera Yaw", &rotation(0), 0.0f, 360.0f);
//	ImGui::SliderFloat("Camera Pitch", &rotation(1), -89.0f, 89.0f);
//	ImGui::Separator();
//
//	char buf[32];
//	static char text_bufs[3 * 5][16];
//	static ImGuiTableFlags flags = ImGuiTableFlags_Borders;
//	ImGui::Text("Camera Translation:");
//	if (ImGui::BeginTable("Camera Translation", 3))
//	{
//		ImGui::TableNextRow();
//		ImGui::TableSetColumnIndex(0);
//		ImGui::PushButtonRepeat(true);
//		if (ImGui::ArrowButton("##up", ImGuiDir_Up)) { translation[4] = false; }
//		else { translation[4] = true; }
//		ImGui::PopButtonRepeat();
//
//		ImGui::TableSetColumnIndex(1);
//		ImGui::PushButtonRepeat(true);
//		if (ImGui::Button(" W ")) { translation[0] = false; }
//		else { translation[0] = true; }
//		ImGui::PopButtonRepeat();
//
//		ImGui::TableSetColumnIndex(2);
//		ImGui::PushButtonRepeat(true);
//		if (ImGui::ArrowButton("##down", ImGuiDir_Down)) { translation[5] = false; }
//		else { translation[5] = true; }
//		ImGui::PopButtonRepeat();
//
//		ImGui::TableNextRow();
//		ImGui::TableSetColumnIndex(0);
//		ImGui::PushButtonRepeat(true);
//		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { translation[2] = false; }
//		else { translation[2] = true; }
//		ImGui::PopButtonRepeat();
//
//		ImGui::TableSetColumnIndex(1);
//		ImGui::PushButtonRepeat(true);
//		if (ImGui::Button(" A ")) { translation[1] = false; }
//		else { translation[1] = true; }
//		ImGui::PopButtonRepeat();
//
//		ImGui::TableSetColumnIndex(2);
//		ImGui::PushButtonRepeat(true);
//		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { translation[3] = false; }
//		else { translation[3] = true; }
//		ImGui::PopButtonRepeat();
//		ImGui::EndTable();
//	}
//
//	ImGui::Text("Camera Position: ");
//	if (ImGui::BeginTable("Target Values", 3, flags))
//	{
//		ImGui::TableNextRow();
//		ImGui::TableSetColumnIndex(0);
//		sprintf_s(buf, "X: %1.3f", m_Position(0));
//		ImGui::TextUnformatted(buf);
//
//		ImGui::TableSetColumnIndex(1);
//		sprintf_s(buf, "Y: %1.3f", m_Position(1));
//		ImGui::TextUnformatted(buf);
//
//		ImGui::TableSetColumnIndex(2);
//		sprintf_s(buf, "Z: %1.3f", m_Position(2));
//		ImGui::TextUnformatted(buf);
//		ImGui::EndTable();
//	}
//
//	ImGui::Text("Camera Target: ");
//	if (ImGui::BeginTable("Target Values", 3, flags))
//	{
//		ImGui::TableNextRow();
//		ImGui::TableSetColumnIndex(0);
//		sprintf_s(buf, "X: %1.3f", m_Target(0));
//		ImGui::TextUnformatted(buf);
//
//		ImGui::TableSetColumnIndex(1);
//		sprintf_s(buf, "Y: %1.3f", m_Target(1));
//		ImGui::TextUnformatted(buf);
//
//		ImGui::TableSetColumnIndex(2);
//		sprintf_s(buf, "Z: %1.3f", m_Target(2));
//		ImGui::TextUnformatted(buf);
//		ImGui::EndTable();
//	}
//
//	ImGui::Text("Camera Basis: ");
//	if (ImGui::BeginTable("Basis Values", 3, flags))
//	{
//		ImGui::TableNextRow();
//		for (int column = 0; column < 3; column++)
//		{
//			ImGui::TableSetColumnIndex(column);
//			sprintf_s(buf, "X: %1.3f", m_RightBasis(column));
//			ImGui::TextUnformatted(buf);
//		}
//		ImGui::TableNextRow();
//		for (int column = 0; column < 3; column++)
//		{
//			ImGui::TableSetColumnIndex(column);
//			sprintf_s(buf, "Y: %1.3f", m_UpwardBasis(column));
//			ImGui::TextUnformatted(buf);
//		}
//		ImGui::TableNextRow();
//		for (int column = 0; column < 3; column++)
//		{
//			ImGui::TableSetColumnIndex(column);
//			sprintf_s(buf, "Z: %1.3f", m_ForwardBasis(column));
//			ImGui::TextUnformatted(buf);
//		}
//		ImGui::EndTable();
//	}
//
//	if (!ImGui::Checkbox("Lock Camera", &islocked))
//	{
//		CheckTranslationInput(&translation[0], 1.0f);
//		RotateCamera(rotation);
//	}
//
//	ImGui::SameLine();
//	if (ImGui::Button("Reset Camera"))
//	{
//		*this = Camera();
//		rotation = { 90.0f, 0.0f };
//	}
//	ImGui::Separator();
//
//}