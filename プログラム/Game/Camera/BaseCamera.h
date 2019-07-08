#pragma once

class BaseCamera
{
	// 一応ディフォルト値を定義するけど調整して下さい
	static const float CAMERA_K;		//	ばね係数
	static const float CAMERA_M;		//	摩擦係数
	static const float CAMERA_DISTANCE;	//	基準の距離

protected:

	// 視点の位置
	DirectX::SimpleMath::Vector3 m_eyePt;

	// 注目点の位置
	DirectX::SimpleMath::Vector3 m_targetPt;

	// 移動する速さ(視点）
	DirectX::SimpleMath::Vector3 m_eyeSpeed;

	// 移動する速さ(注目点）
	DirectX::SimpleMath::Vector3 m_targetSpeed;

	//	ばね係数
	float m_k;

	//	摩擦係数
	float m_m;

	//	距離に応じてばね係数を変化させるための基準の距離
	float m_distance;

	// カメラの位置の初期化フラグ
	bool m_resetFlag;

public:
	// コンストラクタ
	BaseCamera();

	// デストラクタ
	virtual ~BaseCamera() {}

	// ばね係数を設定する関数
	void SetCameraK(float k) { m_k = k; }

	// 摩擦係数を設定する関数
	void SetCameraM(float m) { m_m = m; }

	//	距離に応じてばね係数を変化させるための基準の距離を設定する関数
	void SetCameraDistance(float distance) { m_distance = distance; }

	// カメラの切り替え時の初期化関数（切り替え時に呼び出すと補間しないよ！）
	void ResetCamera()
	{
		m_resetFlag = true;
	}

	// カメラの位置とターゲットを指定する関数
	void SetPositionTarget(DirectX::SimpleMath::Vector3& eye, DirectX::SimpleMath::Vector3& target);

	// 視点の位置を取得する関数
	DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eyePt; }

	// 注目点の位置を取得する関数
	DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_targetPt; }
};