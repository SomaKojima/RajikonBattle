#include "../../pch.h"
#include "Accel.h"

const float Command::Accel::MOVE_SPEED = 0.02f;

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// 　コンストラクタ
/// </summary>
/// <returns></returns>
Command::Accel::Accel()
	:
	m_dir(Vector3::Zero)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Command::Accel::~Accel()
{
}

void Command::Accel::Excute(GameObject & obj)
{
	float speed = MOVE_SPEED;
	Transform& transform = obj.GetTransform();
	Vector3 vec = m_dir * speed;
	Vector3 accel = transform.WorldAccel() + Vector3::Transform(vec, transform.WorldDir());
	transform.WorldAccel(accel);
}
