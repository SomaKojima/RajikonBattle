#include "../../pch.h"
#include "Friction.h"
#include "../../DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Friction::Friction()
	:
	m_normal(Vector3::Up),
	m_isHit(false)
{
}

Friction::~Friction()
{
}

void Friction::LateUpdate(float elapsedTime)
{
	float friction = 0.9f;

	Vector3 vel = m_gameObject->GetTransform().WorldVel() * friction;
	m_gameObject->GetTransform().WorldVel(vel);

	// ‰Á‘¬“x‚É–€C‚ğ‰Á‚¦‚é
	Vector3 accel = m_gameObject->GetTransform().WorldAccel() * friction;
	m_gameObject->GetTransform().WorldAccel(accel);
}

// Õ“Ë‚Ìˆ—
void Friction::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	
}
