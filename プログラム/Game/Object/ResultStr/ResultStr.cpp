#include "../../../pch.h"
#include "ResultStr.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultStr::ResultStr()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultStr::~ResultStr()
{
}

/// <summary>
/// ����
/// </summary>
void ResultStr::Instance(Type type)
{
	// �摜�`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* twoDimentionSprite = nullptr;
	switch (type)
	{
	case ResultStr::You:
		twoDimentionSprite = new TwoDimentionSprite(YouWinTexture::GetInstace().GetTexture(), YouWinTexture::GetInstace().GetRect());
		break;
	case ResultStr::Npc:
		twoDimentionSprite = new TwoDimentionSprite(NPCWinTexture::GetInstace().GetTexture(), NPCWinTexture::GetInstace().GetRect());
		break;
	case ResultStr::Time:
		twoDimentionSprite = new TwoDimentionSprite(TimeUpTexture::GetInstace().GetTexture(), TimeUpTexture::GetInstace().GetRect());
		break;
	}
	AddComponent(twoDimentionSprite);
}
