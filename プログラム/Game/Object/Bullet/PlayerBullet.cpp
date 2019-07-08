#include "../../pch.h"
#include "PlayerBullet.h"

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
PlayerBullet::PlayerBullet()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBullet::~PlayerBullet()
{
}

/// <summary>
/// 生成
/// </summary>
void PlayerBullet::Instance()
{
	SetName("Bullet");
	SetTag(Tag::Tag_BulletPlayer1);
	// モデル取得
	ModelData& modelData = BulletModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// 球の当たり判定を作成
	CollisionSphere* collisionSphere = new CollisionSphere(Vector3::Zero, 0.5f);
	AddComponent(collisionSphere);
	//// 重力のコンポーネントを作成
	//Gravity* gravity = new Gravity();
	//gravity->SetGravity(8.0f);
	//AddComponent(gravity);
	// 弾の時間
	BulletLife* bulletLife = new BulletLife();
	AddComponent(bulletLife);
}
