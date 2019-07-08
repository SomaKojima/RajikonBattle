#pragma once

#include "../Utility/Singleton.h"

/// <summary>
/// �J�����̊Ǘ�
/// </summary>
class CameraManager : public Singleton<CameraManager>
{
public:
	// �R���X�g���N�^
	CameraManager();
	// �f�X�g���N�^
	~CameraManager();

public:

	// �r���[�̐ݒ�
	void SetView(DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// �r���[�̎擾
	DirectX::SimpleMath::Matrix& GetView() { return m_view; }

private:
	// �J�����̃r���[
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_targetPos;
};
