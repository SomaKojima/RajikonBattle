#include "../../pch.h"
#include "Enemy.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/EnemyControllerr.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Component/Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy(Transform* target)
	:
	m_target(target)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// 生成
/// </summary>
void Enemy::Instance()
{
	SetName("Enemy");
	SetTag(Tag::Tag_Player2);
	// モデル取得
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	RenderThreeDimention* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// 球の当たり判定を作成
	CollisionSphere* collisionSphere = new CollisionSphere(Vector3::Zero, 1.5f);
	AddComponent(collisionSphere);
	// 重力のコンポーネントを作成
	Gravity* gravity = new Gravity();
	AddComponent(gravity);
	// 摩擦のコンポーネントを作成
	Friction* friction = new Friction();
	AddComponent(friction);
	// 敵の操作のコンポーネントを作成
	EnemyController* enemyController = new EnemyController(m_target);
	AddComponent(enemyController);
	// 姿勢制御のコンポーネントを作成
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
	// 体力のコンポーネントを作成
	StatusHP* statusHP = new StatusHP(100);
	AddComponent(statusHP);

}
