#pragma once

#include <list>

class GameObject;

/// <summary>
/// 変形のクラス
/// </summary>
class Transform
{
public:
	// コンストラクタ
	Transform();

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);

	// ワールド座標を座標を取得
	void WorldPos(const DirectX::SimpleMath::Vector3& pos);
	const DirectX::SimpleMath::Vector3& WorldPos();

	// ワールド速度を取得
	DirectX::SimpleMath::Vector3 WorldVel();
	void WorldVel(DirectX::SimpleMath::Vector3& vel);

	// ワールド加速度を取得
	DirectX::SimpleMath::Vector3 WorldAccel();
	void WorldAccel(DirectX::SimpleMath::Vector3& accel);

	// ローカル座標の向きを取得する
	DirectX::SimpleMath::Quaternion LocalDir();
	void LocalDir(DirectX::SimpleMath::Quaternion& localDir);
	// ワールド向きを取得
	DirectX::SimpleMath::Quaternion WorldDir();
	void WorldDir(DirectX::SimpleMath::Quaternion& dir);

	// ローカル座標の逆向きを取得する
	DirectX::SimpleMath::Quaternion LocalInvDir();
	void LocalInvDir(DirectX::SimpleMath::Quaternion inv);
	// ワールド逆向きを取得
	DirectX::SimpleMath::Quaternion WorldInvDir();

	// ワールドマトリクス取得
	DirectX::SimpleMath::Matrix WorldMatrix() { return m_worldMatrix; }
	void WorldMatrix(DirectX::SimpleMath::Matrix& matrix) { m_worldMatrix = matrix; }


	// 自身のゲームオブジェクトを設定する
	void SetGameObject(GameObject* gameObject) { m_gameObject = gameObject; }
	// 自身のゲームオブジェクトを取得
	GameObject* GetGameObject() { return m_gameObject; }

private:
	//// 座標・速度・加速度のローカル座標の取得の計算
	//DirectX::SimpleMath::Vector3 GetWorldToLocal(DirectX::SimpleMath::Vector3 world, DirectX::SimpleMath::Vector3 parentWorld);
	//// 座標・速度・加速度のローカル座標の設定の計算
	//DirectX::SimpleMath::Vector3 SetLocalToWorld(DirectX::SimpleMath::Vector3& local);

	// 子の座標を更新する
	void UpdateChildPos(DirectX::SimpleMath::Vector3& pos);
	// 子供のマトリクスを更新する
	void UpdateChildMatrix(float elapsedTime);

	//DirectX::SimpleMath::Quaternion FromToRotation(DirectX::SimpleMath::Vector3& fromNormalize, DirectX::SimpleMath::Vector3& toNormalize);

private:
	DirectX::SimpleMath::Vector3 m_worldPos;		// 座標

	DirectX::SimpleMath::Vector3 m_worldVel;		// 速度
	DirectX::SimpleMath::Vector3 m_worldAccel;		// 加速度
	DirectX::SimpleMath::Quaternion m_localDir;		// 向き
	DirectX::SimpleMath::Quaternion m_localInvDir;	// 逆向き
	DirectX::SimpleMath::Matrix m_worldMatrix;		// マトリクス

private:	
	GameObject* m_gameObject;				// 自身のゲームオブジェクト
};