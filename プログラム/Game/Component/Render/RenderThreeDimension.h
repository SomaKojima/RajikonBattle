#pragma once

#include "../Component.h"

/// <summary>
/// 3Dモデル描画のコンポーネント
/// </summary>
class RenderThreeDimention : public Component
{
public:
	// 描画する種類
	enum Type
	{
		Nomal,
		Sky
	};

public:
	// コンストラクタ
	RenderThreeDimention(DirectX::Model* model, Type type);
	// デストラクタ
	~RenderThreeDimention();

public:
	// 描画
	void Render()override;
	// 終了
	void Finalize()override;

	void SetEmissionColor(DirectX::SimpleMath::Vector3 color) { m_emissionColor = color; }
private:
	// 描画する種類
	Type m_type;
	// 描画するモデル
	DirectX::Model* m_model;
	DirectX::SimpleMath::Vector3 m_emissionColor;
};