#include "../../pch.h"
#include "CameraManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CameraManager::CameraManager()
	:
	m_view(Matrix::Identity),
	m_pos(Vector3::Zero),
	m_targetPos(Vector3::Zero)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CameraManager::~CameraManager()
{
}
