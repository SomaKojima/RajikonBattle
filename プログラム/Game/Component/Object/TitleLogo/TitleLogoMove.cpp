#include "../../pch.h"
#include "TitleLogoMove.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
TitleLogoMove::TitleLogoMove(float y)
	:
	m_isFall(true),
	m_y(y),
	m_time(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleLogoMove::~TitleLogoMove()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void TitleLogoMove::Update(float elapsedTime)
{
	Transform& transform = m_gameObject->GetTransform();
	if (m_isFall)
	{
		float speedY = 0.01f;
		Vector3 accel = Vector3(0.0f, speedY, 0.0f) + transform.WorldAccel();
		transform.WorldAccel(accel);
		if (m_y < transform.WorldPos().y)
		{
			m_isFall = false;
		}
	}
	else
	{
		Vector3 accel = Vector3::Zero;
		transform.WorldAccel(accel);

		Vector3 vel = Vector3::Zero;
		transform.WorldVel(vel);

		Vector3 pos = transform.WorldPos();
		pos.y = m_y + 10.0f * cos(m_time * 3);
		transform.WorldPos(pos);
		m_time += elapsedTime;
	}

}
