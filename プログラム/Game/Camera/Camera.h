#pragma once
#include "../Object/GameObject.h"

class PlayCamera;

class Camera : public GameObject
{
public:
	// コンストラクタ
	Camera();
	// デストラクタ
	~Camera();

	// プレイシーンのカメラ
	void InitializePlay(GameObject* player);
	// タイトルシーンのカメラ
	void InitializeTitle();

public:
	// 生成関数
	void Instance() override;

	PlayCamera* GetPlayCamera() { return m_playCamera; }

private:
	PlayCamera* m_playCamera;
};