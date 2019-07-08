#pragma once

#include "../Utility/Singleton.h"

/// <summary>
/// カメラの管理
/// </summary>
class CameraManager : public Singleton<CameraManager>
{
public:
	// コンストラクタ
	CameraManager();
	// デストラクタ
	~CameraManager();

public:

	// ビューの設定
	void SetView(DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// ビューの取得
	DirectX::SimpleMath::Matrix& GetView() { return m_view; }

private:
	// カメラのビュー
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_targetPos;
};
