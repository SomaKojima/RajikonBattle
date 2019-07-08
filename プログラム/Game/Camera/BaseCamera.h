#pragma once

class BaseCamera
{
	// �ꉞ�f�B�t�H���g�l���`���邯�ǒ������ĉ�����
	static const float CAMERA_K;		//	�΂ˌW��
	static const float CAMERA_M;		//	���C�W��
	static const float CAMERA_DISTANCE;	//	��̋���

protected:

	// ���_�̈ʒu
	DirectX::SimpleMath::Vector3 m_eyePt;

	// ���ړ_�̈ʒu
	DirectX::SimpleMath::Vector3 m_targetPt;

	// �ړ����鑬��(���_�j
	DirectX::SimpleMath::Vector3 m_eyeSpeed;

	// �ړ����鑬��(���ړ_�j
	DirectX::SimpleMath::Vector3 m_targetSpeed;

	//	�΂ˌW��
	float m_k;

	//	���C�W��
	float m_m;

	//	�����ɉ����Ă΂ˌW����ω������邽�߂̊�̋���
	float m_distance;

	// �J�����̈ʒu�̏������t���O
	bool m_resetFlag;

public:
	// �R���X�g���N�^
	BaseCamera();

	// �f�X�g���N�^
	virtual ~BaseCamera() {}

	// �΂ˌW����ݒ肷��֐�
	void SetCameraK(float k) { m_k = k; }

	// ���C�W����ݒ肷��֐�
	void SetCameraM(float m) { m_m = m; }

	//	�����ɉ����Ă΂ˌW����ω������邽�߂̊�̋�����ݒ肷��֐�
	void SetCameraDistance(float distance) { m_distance = distance; }

	// �J�����̐؂�ւ����̏������֐��i�؂�ւ����ɌĂяo���ƕ�Ԃ��Ȃ���I�j
	void ResetCamera()
	{
		m_resetFlag = true;
	}

	// �J�����̈ʒu�ƃ^�[�Q�b�g���w�肷��֐�
	void SetPositionTarget(DirectX::SimpleMath::Vector3& eye, DirectX::SimpleMath::Vector3& target);

	// ���_�̈ʒu���擾����֐�
	DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eyePt; }

	// ���ړ_�̈ʒu���擾����֐�
	DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_targetPt; }
};