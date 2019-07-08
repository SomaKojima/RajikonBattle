#include "../../pch.h"
#include "Camera.h"
#include "PlayCamera.h"
#include "TitleCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target"></param>
Camera::Camera()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// �v���C�V�[���̃J�����̏�����
/// </summary>
/// <param name="target"></param>
void Camera::InitializePlay(GameObject * target)
{
	// �J�����̃R���|�[�l���g���쐬
	m_playCamera = new PlayCamera(target);
	AddComponent(m_playCamera);
}

/// <summary>
/// �^�C�g���V�[���̃J�����̏�����
/// </summary>
void Camera::InitializeTitle()
{
	Component* titleCamera = new TitleCamera();
	AddComponent(titleCamera);
}

/// <summary>
/// �����֐�
/// </summary>
void Camera::Instance()
{
}
