
#pragma once

#include "CollisionComponent.h"
#include "../../Collision/DebugCollision/DebugMesh.h"


/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionMesh : public CollisionComponent
{
public:
	CollisionMesh(wchar_t* fil, float radius);
	~CollisionMesh();

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

private:
	// 「.obj」のファイル名
	wchar_t* m_file;
	// ファイルが見つかったフラグ
	bool m_isFile;

	// 当たり判定の空間に登録するための半径（バウンディング）
	float m_radius;

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugMesh> m_obj;
};
