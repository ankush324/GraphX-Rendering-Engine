#include "pch.h"
#include "Camera.h"

#include "Timer/Clock.h"

/* Input */
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

namespace engine
{
	Camera::Camera(const gm::Vector3& CameraPos, const gm::Vector3& LookAtPoint, const gm::Vector3& UpAxis, float AspectRatio, float Near, float Far, float FOV)
		: m_WorldUpAxis(UpAxis), m_AspectRatio(AspectRatio), m_Near(Near), m_Far(Far), m_RenderStateDirty(true), CameraSpeed(5.5f), CameraPosition(CameraPos), EulerAngles(0), m_ViewAxis(), m_RightAxis(0), FieldOfView(FOV)
	{
		m_ViewAxis = LookAtPoint - CameraPosition;
		m_ViewAxis.Normalize();

		m_RightAxis = gm::Vector3::CrossProduct(m_ViewAxis, m_WorldUpAxis);
		m_RightAxis.Normalize();

		m_UpAxis = gm::Vector3::CrossProduct(m_RightAxis, m_ViewAxis);
	}

	void Camera::Update(float DeltaTime)
	{
		ProcessKeyboardInput(DeltaTime);
		ProcessMouseInput(DeltaTime);
	}

	void Camera::ProcessKeyboardInput(float DeltaTime)
	{
		// Update the camera position
		if (Mouse::GetMouse()->IsRightButtonPressed())
		{
			float CurrentCameraSpeed = CameraSpeed * DeltaTime;
			const std::shared_ptr<Keyboard>& keyboard = Keyboard::GetKeyboard();
			m_RenderStateDirty = true;
			
			if (keyboard->GetKey(Keys::GX_W))
			{
				CameraPosition += CurrentCameraSpeed * m_ViewAxis;
			}
			else if (keyboard->GetKey(Keys::GX_S))
			{
				CameraPosition -= CurrentCameraSpeed * m_ViewAxis;
			}
			else if (keyboard->GetKey(Keys::GX_A))
			{
				CameraPosition -= CurrentCameraSpeed * m_RightAxis;
			}
			else if (keyboard->GetKey(Keys::GX_D))
			{
				CameraPosition += CurrentCameraSpeed * m_RightAxis;
			}
			else if (keyboard->GetKey(Keys::GX_E))
			{
				CameraPosition += CurrentCameraSpeed * m_UpAxis;
			}
			else if (keyboard->GetKey(Keys::GX_Q))
			{
				CameraPosition -= CurrentCameraSpeed * m_UpAxis;
			}
			else
			{
				m_RenderStateDirty = false;
			}
		}
	}

	void Camera::ProcessMouseInput(float DeltaTime)
	{
		if (Mouse::GetMouse()->IsRightButtonPressed())
		{
			const std::shared_ptr<Mouse>& mouse = Mouse::GetMouse();
			const gm::Vector2 LastPosition = mouse->GetLastPosition();
			const gm::Vector2 CurrentPosition = mouse->GetPosition();

			// Calculate the Yaw and the Pitch offset
			float xOffset = CurrentPosition.x - LastPosition.x;
			float yOffset = CurrentPosition.y - LastPosition.y;
			
			if ((xOffset != 0 && gm::MathUtil::Abs(xOffset) < 20.0f) || (yOffset != 0 && gm::MathUtil::Abs(yOffset) < 20.0f))
			{
				xOffset *= DeltaTime;
				yOffset *= DeltaTime;

				m_RenderStateDirty = true;

				EulerAngles.x += yOffset;
				EulerAngles.y += xOffset;

				if (EulerAngles.x >= 89.0f)
					EulerAngles.x = 89.0f;
				else if (EulerAngles.x <= -89.0f)
					EulerAngles.x = -89.0f;

				gm::MathUtil::ClampAngle(EulerAngles.y);

				m_RightAxis = gm::Vector3::CrossProduct(m_ViewAxis, m_WorldUpAxis);
				m_ViewAxis = gm::Vector3(gm::Rotation(xOffset, m_UpAxis) * gm::Rotation(-yOffset, m_RightAxis) * gm::Vector4(m_ViewAxis, 1.0f));
				m_UpAxis = gm::Vector3::CrossProduct(m_RightAxis, m_ViewAxis);
			}
		}

		// Check for the mouse scroll
		if (Mouse::GetMouse()->GetScrollOffset() != gm::Vector2::ZeroVector)
		{
			gm::Vector2 Offset = Mouse::GetMouse()->GetScrollOffset();
			FieldOfView -= Offset.y;

			m_RenderStateDirty = true;
		}
	}

	void Camera::Enable(class Shader& shader, const std::string& Name) const
	{
	}

	void Camera::Disable() const
	{
	}
}