#include "../../pch.h"
#include "EnemyBullet.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Collision/CollisionSphere.h"
#include "../../Component/Object/BulletLife.h"

#include"../../Data/Model/ModelData.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBullet::EnemyBullet()
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBullet::~EnemyBullet()
{
}

/// <summary>
/// 生成
/// </summary>
void EnemyBullet::Instance()
{
	SetTag(Tag::Tag_BulletPlayer2);
	// モデル取得
	ModelData& modelData = BulletModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// 球の当たり判定を作成
	CollisionSphere* collisionSphere = new CollisionSphere(Vector3::Zero, 0.5f);
	//collisionSphere->SetBound(true);
	AddComponent(collisionSphere);
	// 弾の時間
	BulletLife* bulletLife = new BulletLife();
	AddComponent(bulletLife);
}
