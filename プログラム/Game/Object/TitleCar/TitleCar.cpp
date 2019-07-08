#include "../../pch.h"
#include "TitleCar.h"

#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Physics/Gravity.h"
#include "../../Component/Physics/Friction.h"
#include "../../Component/Controller/TitlePlayerController.h"
#include "../../Component/Object/PositionControl.h"

#include "../../Component/Collision/CollisionSphere.h"

#include"../../Data/Model/ModelData.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
TitleCar::TitleCar()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleCar::~TitleCar()
{
}

/// <summary>
/// 生成
/// </summary>
void TitleCar::Instance()
{

	SetName("Player");
	SetTag(Tag::Tag_Player1);
	// モデル取得
	ModelData& modelData = CarBodyModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
	// 球の当たり判定を作成
	Component* collisionSphere = new CollisionSphere(Vector3::Zero, 1.5f);
	AddComponent(collisionSphere);
	// タイトル時の操作
	Component* controller = new TitlePlayerController();
	AddComponent(controller);
	// 重力のコンポーネントを作成
	Component* gravity = new Gravity();
	AddComponent(gravity);
	// 摩擦のコンポーネントを作成
	Component* friction = new Friction();
	AddComponent(friction);
	// 姿勢制御のコンポーネントを作成
	PositionControl* positionControl = new PositionControl();
	AddComponent(positionControl);
}
