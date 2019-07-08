#pragma once

#include "BaseCamera.h"
#include "../Component/Component.h"

class GameObject;

/// <summary>
/// プレイシーンのカメラ
/// </summary>
class PlayCamera : public BaseCamera, public Component
{
public:
	enum CAMERA_TYPE
	{
		PLAY,
		RESULT
	};
private:
	// 追いかける相手
	GameObject* m_target;

	float m_y;

	float m_rotation;
	CAMERA_TYPE m_type;
public:
	// コンストラクタ
	PlayCamera(GameObject* targe);

	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float elapsedTime) override;

	void PlayScene(float elapsedTime);

	void ResultScene(float elapsedTime);

	void SetTarget(GameObject* target) { m_target = target; }

	void SetType(CAMERA_TYPE type) { m_type = type; }
};