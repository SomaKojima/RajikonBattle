#include "../../../pch.h"
#include "HPBar.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Component/Object/HPBar/HPBarManager.h"
#include "../../Component/Object/StatusHP.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// コンストラクタ
/// </summary>
HPBar::HPBar()
{
}

/// <summary>
/// デストラクタ
/// </summary>
HPBar::~HPBar()
{
}

/// <summary>
/// 生成
/// </summary>
void HPBar::Instance(GameObject* obj, TYPE type)
{
	// 画像のデータを取得する
	HPBarFlameTexture& hpbarFlameTexture = HPBarFlameTexture::GetInstace();
	HPBarGreenTexture& hpBarGreenTexture = HPBarGreenTexture::GetInstace();
	TextureData* hpBarStrTexture = &HPBarStrPlayerTexture::GetInstace();
	if (type == Enemy)
	{
		hpBarStrTexture = &HPBarStrEnemyTexture::GetInstace();
	}

	float scale = 0.5f;

	// 画像<フレーム>描画のコンポーネントを作成
	TwoDimentionSprite* flameRenderer = new TwoDimentionSprite(hpbarFlameTexture.GetTexture(), hpbarFlameTexture.GetRect());
	flameRenderer->SetOrigin(DirectX::SimpleMath::Vector2::Zero);
	flameRenderer->SetScale(scale);
	AddComponent(flameRenderer);

	// 画像＜緑＞描画のコンポーネントを作成
	TwoDimentionSprite* greenRenderer = new TwoDimentionSprite(hpBarGreenTexture.GetTexture(), hpBarGreenTexture.GetRect());
	greenRenderer->SetOrigin(DirectX::SimpleMath::Vector2::Zero);
	greenRenderer->SetScale(scale);
	AddComponent(greenRenderer);

	// 画像＜文字＞描画のコンポーネントを作成
	TwoDimentionSprite* strRenderer = new TwoDimentionSprite(hpBarStrTexture->GetTexture(), hpBarStrTexture->GetRect());
	strRenderer->SetOrigin(DirectX::SimpleMath::Vector2::Zero);
	strRenderer->SetScale(scale);
	AddComponent(strRenderer);

	// 緑の部分の管理コンポーネントを作成
	StatusHP* hp = obj->GetComponent<StatusHP>();
	HPBarManager* hpBarManager = new HPBarManager(greenRenderer, hpBarGreenTexture.GetRect(), hp);
	AddComponent(hpBarManager);

}
