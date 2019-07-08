#include "../../pch.h"
#include "CollisionComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CollisionComponent::CollisionComponent(MyCollisionObject::CollisionObject* collisionObject)
	:
	m_collisionObject(collisionObject)
{
}

CollisionComponent::~CollisionComponent()
{
	delete m_collisionObject;
}

/// <summary>
/// èIóπèàóù
/// </summary>
void CollisionComponent::Finalize()
{
}

