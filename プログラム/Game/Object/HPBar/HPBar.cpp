#include "../../../pch.h"
#include "HPBar.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Component/Object/HPBar/HPBarManager.h"
#include "../../Component/Object/StatusHP.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
HPBar::HPBar()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HPBar::~HPBar()
{
}

/// <summary>
/// ����
/// </summary>
void HPBar::Instance(GameObject* obj, TYPE type)
{
	// �摜�̃f�[�^���擾����
	HPBarFlameTexture& hpbarFlameTexture = HPBarFlameTexture::GetInstace();
	HPBarGreenTexture& hpBarGreenTexture = HPBarGreenTexture::GetInstace();
	TextureData* hpBarStrTexture = &HPBarStrPlayerTexture::GetInstace();
	if (type == Enemy)
	{
		hpBarStrTexture = &HPBarStrEnemyTexture::GetInstace();
	}

	float scale = 0.5f;

	// �摜<�t���[��>�`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* flameRenderer = new TwoDimentionSprite(hpbarFlameTexture.GetTexture(), hpbarFlameTexture.GetRect());
	flameRenderer->SetOrigin(DirectX::SimpleMath::Vector2::Zero);
	flameRenderer->SetScale(scale);
	AddComponent(flameRenderer);

	// �摜���΁��`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* greenRenderer = new TwoDimentionSprite(hpBarGreenTexture.GetTexture(), hpBarGreenTexture.GetRect());
	greenRenderer->SetOrigin(DirectX::SimpleMath::Vector2::Zero);
	greenRenderer->SetScale(scale);
	AddComponent(greenRenderer);

	// �摜���������`��̃R���|�[�l���g���쐬
	TwoDimentionSprite* strRenderer = new TwoDimentionSprite(hpBarStrTexture->GetTexture(), hpBarStrTexture->GetRect());
	strRenderer->SetOrigin(DirectX::SimpleMath::Vector2::Zero);
	strRenderer->SetScale(scale);
	AddComponent(strRenderer);

	// �΂̕����̊Ǘ��R���|�[�l���g���쐬
	StatusHP* hp = obj->GetComponent<StatusHP>();
	HPBarManager* hpBarManager = new HPBarManager(greenRenderer, hpBarGreenTexture.GetRect(), hp);
	AddComponent(hpBarManager);

}
