#include "../../pch.h"
#include "StatusHP.h"
#include "../../Camera/PlayCamera.h"
#include "../../Scene/SceneManager.h"
#include "../../Data/Data.h"
#include "../../Object/GameManager/GameManager.h"
#include "GameJudge.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
StatusHP::StatusHP(int hp)
	:
	m_hp(hp),
	m_maxHp(hp),
	m_isStop(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
StatusHP::~StatusHP()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void StatusHP::Update(float elapsedTime)
{
	if (m_gameObject->GetTransform().WorldPos().y < -100)
	{
		m_hp = 0;
	}
}

/// <summary>
/// 衝突
/// </summary>
/// <param name="obj"></param>
/// <param name="collisionObject"></param>
/// <param name="hitPos"></param>
void StatusHP::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
	if (m_isStop) return;
	if (obj.GetTag() == Tag::Tag_BulletPlayer1 || obj.GetTag() == Tag::Tag_BulletPlayer2)
	{
		m_hp -= 10;
	}
	if (m_hp < 0)
	{
		m_hp = 0;
	}
}
