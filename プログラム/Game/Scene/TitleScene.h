#pragma once
#include"SceneManager.h"

#include "../../ADX2/ADX2Le.h"
/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public Scene
{
public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene();

public:
	// �����֐�
	void Instance() override;

private:
	MyLibrary::ADX2Le* m_a;

	CriAtomExPlaybackId m_id;
};
