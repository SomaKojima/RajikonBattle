//--------------------------------------------------------------------------------------
// File: Camera.cpp
//
// �J�����N���X
//
// Date: 2018.7.9
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "../../pch.h"
#include "BaseCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �K���Ȓl�ł�
const float BaseCamera::CAMERA_K = 1.0f / 10.0f;		//	�΂ˌW��
const float BaseCamera::CAMERA_M = 1.0f / 10.0f;		//	���C�W��
const float BaseCamera::CAMERA_DISTANCE = 10.0f;	//	��̋���

BaseCamera::BaseCamera()
	: m_resetFlag(true), m_k(CAMERA_K), m_m(CAMERA_M), m_distance(CAMERA_DISTANCE)
{
}

void BaseCamera::SetPositionTarget(Vector3& eye, Vector3& target)
{
	// �J�����؂�ւ����ȂǕ�Ԃ������Ȃ��ꍇ��InitializeCamera�֐����Ăт����Ă�������
	if (m_resetFlag == true)
	{
		m_resetFlag = false;
		m_eyePt = eye;
		m_targetPt = target;
		m_eyeSpeed = m_targetSpeed = Vector3(0.0f, 0.0f, 0.0f);
		return;
	}

	// ���_�ƒ��ړ_�̋������擾
	Vector3 vec = eye - target;
	float dis = vec.Length();

	// �΂ˌW�����J�����ƃ^�[�Q�b�g�̋����ɉ����ĕύX����
	m_eyeSpeed += (eye - m_eyePt) * m_k * m_distance / dis;
	m_eyeSpeed -= m_eyeSpeed * m_m;
	m_eyePt += m_eyeSpeed;
	//m_eyePt = eye;

	// �΂ˌW�����J�����ƃ^�[�Q�b�g�̋����ɉ����ĕύX����
	m_targetSpeed += (target - m_targetPt) * m_k * m_distance / dis;
	m_targetSpeed -= m_targetSpeed * m_m;
	m_targetPt += m_targetSpeed;
	//m_targetPt = target;
}
