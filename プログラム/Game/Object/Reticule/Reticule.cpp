#include "../../../pch.h"
#include "Reticule.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Reticule::Reticule()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Reticule::~Reticule()
{
}

/// <summary>
/// ����
/// </summary>
void Reticule::Instance()
{
	// �摜�̃f�[�^���擾����
	ReticuleTexture& textureData = ReticuleTexture::GetInstace();
	RECT rect = textureData.GetRect();

	// �摜�`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);
}
