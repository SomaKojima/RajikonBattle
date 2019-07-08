#include "../../pch.h"
#include "Cannon.h"
#include "../../Component/Render/RenderThreeDimension.h"

#include"../../Data/Model/ModelData.h"

/// <summary>
/// コンストラクタ
/// </summary>
Cannon::Cannon()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Cannon::~Cannon()
{
}

/// <summary>
/// 生成
/// </summary>
void Cannon::Instance()
{
	GetTransform().WorldPos(DirectX::SimpleMath::Vector3(0.0f, 3.0f, 0.0f));
	// モデル取得
	ModelData& modelData = CarCannonModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Nomal);
	AddComponent(renderThreeDimention);
}
