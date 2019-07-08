#include "../../../pch.h"
#include "SkyDome.h"
#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Object/SkyDome/SkyDomeRotation.h"

#include"../../Data/Model/ModelData.h"

/// <summary>
/// コンストラクト
/// </summary>
SkyDome::SkyDome()
{
}

/// <summary>
/// デストラクタ
/// </summary>
SkyDome::~SkyDome()
{
}

/// <summary>
/// 生成
/// </summary>
void SkyDome::Instance()
{
	// 名前を設定する
	SetName("SkyDome");
	// モデル取得
	ModelData& modelData = SkyDomeModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	RenderThreeDimention* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Sky);
	//renderThreeDimention->SetEmissionColor(DirectX::SimpleMath::Vector3::One * 0.8f);
	AddComponent(renderThreeDimention);
	// スカイドームの回転コンポーネントを作成
	SkyDomeRotation* skyDomeRotation = new SkyDomeRotation();
	AddComponent(skyDomeRotation);
}
