#include "../../pch.h"
#include "TitleLogo.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Component/Object/TitleLogo/TitleLogoMove.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleLogo::TitleLogo()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleLogo::~TitleLogo()
{
}

/// <summary>
/// ����
/// </summary>
void TitleLogo::Instance()
{
	// �摜�̃f�[�^���擾����
	TitleLogoTexture& textureData = TitleLogoTexture::GetInstace();

	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);

	TitleLogoMove* titileLogoMove = new TitleLogoMove(200.0f);
	AddComponent(titileLogoMove);
}
