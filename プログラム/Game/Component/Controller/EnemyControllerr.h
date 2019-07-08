#pragma once

#include "../Component.h"

class Transform;

/// <summary>
/// 敵の操作のコンポーネント
/// </summary>
class EnemyController : public Component
{
public:
	static const float ENEMY_SPEED;
	static const float ENEMY_LEFT_ROTATION;
	static const float ENEMY_EYE_RANGE;
	static const float ENEMY_SHOT_SPEED;
	static const float ENEMY_SHOT_TIME;
public:
	// コンストラクタ
	EnemyController(Transform* target);
	// デストラクタ
	~EnemyController();

public:
	// 更新処理
	void Update(float elapsedTime) override;

	void SetIsStop(bool flag) { m_isStop = flag; }
private:

	// ターゲットが視界内に入っているかどうか
	bool IsInEyeRange();

	// ターゲットへ方向を向ける
	void RotationToTarget();

	// 左回転
	void RotationLeft();

	// 前進
	void Addvance();

	void Shot();

	void SetEyeRange(float eyeRange) { m_eyeRange = eyeRange; }

private:
	Transform* m_target;
	float m_eyeRange;
	float m_shotTime;
	bool m_isStop;
};
