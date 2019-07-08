#pragma once

#include "BaseCamera.h"
#include "../Component/Component.h"

class GameObject;

/// <summary>
/// タイトルシーンのカメラ
/// </summary>
class TitleCamera : public BaseCamera, public Component
{
private:
	float m_rotation;
public:
	// コンストラクタ
	TitleCamera();

	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float elapsedTime) override;
};