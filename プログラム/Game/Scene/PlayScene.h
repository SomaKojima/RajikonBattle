#pragma once
#include"SceneManager.h"

#include "../../ADX2/ADX2Le.h"

/// <summary>
/// �v���C�V�[��
/// </summary>
class PlayScene : public Scene
{
public:
	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	~PlayScene();

public:
	// �����֐�
	void Instance() override;

private:
	MyLibrary::ADX2Le* m_a;

	CriAtomExPlaybackId m_id;
};