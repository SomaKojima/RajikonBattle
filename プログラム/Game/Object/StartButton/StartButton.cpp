#include "../../pch.h"
#include "StartButton.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"
#include "../../Component/Object/StartButton/StartButtonMove.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StartButton::StartButton()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StartButton::~StartButton()
{
}

/// <summary>
/// ����
/// </summary>
void StartButton::Instance()
{
	// �摜�̃f�[�^���擾����
	StartButtonTexture& textureData = StartButtonTexture::GetInstace(); 


	TextureData& textureData1 = StartButtonStrTexture::GetInstace();
	TextureData& textureData2 = StartButtonBGTexture::GetInstace();

	// �摜�`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);
	// �X�^�[�g�{�^���̓����̃R���|�[�l���g���쐬
	StartButtonMove* startButtonMove = new StartButtonMove(twoDimentionSprite, textureData.GetRect());
	AddComponent(startButtonMove);

	//// �摜�`��̃R���|�[�l���g���쐬
	//TwoDimentionSprite* twoDimentionSprite2 = new TwoDimentionSprite(textureData2.GetTexture(), textureData2.GetRect());
	//AddComponent(twoDimentionSprite2);

	//// �摜�`��̃R���|�[�l���g���쐬
	//TwoDimentionSprite* twoDimentionSprite1 = new TwoDimentionSprite(textureData1.GetTexture(), textureData1.GetRect());
	//AddComponent(twoDimentionSprite1);

	//// �X�^�[�g�{�^���̓����̃R���|�[�l���g���쐬
	//StartButtonMove* startButtonMove = new StartButtonMove(twoDimentionSprite2, textureData2.GetRect());
	//AddComponent(startButtonMove);
}
