#include "../../../pch.h"
#include "ExitButton.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"
#include "../../Component/Object/ExitButton/ExitButtonMove.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ExitButton::ExitButton()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ExitButton::~ExitButton()
{
}

/// <summary>
/// ����
/// </summary>
void ExitButton::Instance()
{
	// �摜�̃f�[�^���擾����
	ExitButtonTexture& textureData = ExitButtonTexture::GetInstace();

	// �摜�`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);

	// �X�^�[�g�{�^���̓����̃R���|�[�l���g���쐬
	ExitButtonMove* exitButtonMove = new ExitButtonMove(twoDimentionSprite, textureData.GetRect());
	AddComponent(exitButtonMove);
}
