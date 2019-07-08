#pragma once

#include "../Component.h"

class Transform;

/// <summary>
/// �G�̑���̃R���|�[�l���g
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
	// �R���X�g���N�^
	EnemyController(Transform* target);
	// �f�X�g���N�^
	~EnemyController();

public:
	// �X�V����
	void Update(float elapsedTime) override;

	void SetIsStop(bool flag) { m_isStop = flag; }
private:

	// �^�[�Q�b�g�����E���ɓ����Ă��邩�ǂ���
	bool IsInEyeRange();

	// �^�[�Q�b�g�֕�����������
	void RotationToTarget();

	// ����]
	void RotationLeft();

	// �O�i
	void Addvance();

	void Shot();

	void SetEyeRange(float eyeRange) { m_eyeRange = eyeRange; }

private:
	Transform* m_target;
	float m_eyeRange;
	float m_shotTime;
	bool m_isStop;
};
