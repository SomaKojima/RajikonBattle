/// <summary>
/// CollisionSphere.h
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
//#include "../Component.h"
#include "CollisionComponent.h"
#include "../../Collision/DebugCollision/DebugSphere.h"
#include "../../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionSphere : public CollisionComponent
{
public:
	CollisionSphere(DirectX::SimpleMath::Vector3 centerPos, float radius);
	~CollisionSphere();

	// 初期化
	void Initialize() override;

	// 更新
	void Update(float elapsedTime) override;
	// 遅延更新
	void LateUpdate(float elapsedTime) override;
	// 描画
	void Render() override;
	// 終了
	void Finalize() override;

	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& collisionObject, DirectX::SimpleMath::Vector3& hitPos)override;
	
	// 壁刷り
	void HitBack(const MyCollisionObject::Triangle& triangle, DirectX::SimpleMath::Vector3& hitPos);

	// 壁刷りの計算
	DirectX::SimpleMath::Vector3 WallCulc(const DirectX::SimpleMath::Vector3& normal, DirectX::SimpleMath::Vector3 vel, bool boundFlag = false);

	// プロパティ
	DirectX::SimpleMath::Vector3 GetCenterPos() { return m_centerPos; }

	void SetBound(bool isBound) { m_isBound = isBound; }
private:
	DirectX::SimpleMath::Vector3 m_centerPos; // 球の中心

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugSphere> m_obj;
	bool m_isBound;
};
