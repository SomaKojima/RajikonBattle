#include "../../../pch.h"
#include "Player.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/PlayerController.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Component/Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

#include "Cannon.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}

/// <summary>
/// 生成関数
/// </summary>
void Player::Instance()
{
	SetName("Player");
	SetTag(Tag::Tag_Player1);
	// モデル取得
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// 球の当たり判定を作成
	Component* collisionSphere = new CollisionSphere(Vector3::Zero,1.5f);
	AddComponent(collisionSphere);
	// 操作のコンポーネントを作成
	Component* playerController = new PlayerController();
	AddComponent(playerController);
	// 摩擦のコンポーネントを作成
	Component* friction = new Friction();
	AddComponent(friction);
	// 重力のコンポーネントを作成
	Component* gravity = new Gravity();
	AddComponent(gravity);
	// 姿勢制御のコンポーネントを作成
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
	// 体力のコンポーネントを作成
	StatusHP* statusHP = new StatusHP(100);
	AddComponent(statusHP);

	// 子の作成
	/*Cannon* cannon = new Cannon();
	cannon->Instance();
	AddChild(cannon);*/
}
