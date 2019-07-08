#include "../../../pch.h"
#include "Logo.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"
#include "../../Component/Object/Logo/LogoMove.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Logo::Logo()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Logo::~Logo()
{
}

/// <summary>
/// ����
/// </summary>
void Logo::Instance()
{
	// �摜�̃f�[�^���擾����
	TextureData& textureData = LogoTexture::GetInstace();
	RECT rect = textureData.GetRect();

	// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int wwidth = (wRect.right - wRect.left);
	int wheight = (wRect.bottom - wRect.top);

	float scaleX = wwidth / (float)(rect.right / 5);
	float scaleY = wheight / (float)(rect.bottom / 5);

	// �摜�`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	twoDimentionSprite->SetOrigin(Vector2::Zero);
	twoDimentionSprite->SetScale(Vector2(scaleX, scaleY));
	AddComponent(twoDimentionSprite);
	
	// ���S�̓����̃R���|�[�l���g���쐬
	LogoMove* logoMove = new LogoMove(twoDimentionSprite, textureData.GetRect());
	AddComponent(logoMove);
}
