#include "../../../pch.h"
#include "ExitButton.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"
#include "../../Component/Object/ExitButton/ExitButtonMove.h"

/// <summary>
/// コンストラクタ
/// </summary>
ExitButton::ExitButton()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ExitButton::~ExitButton()
{
}

/// <summary>
/// 生成
/// </summary>
void ExitButton::Instance()
{
	// 画像のデータを取得する
	ExitButtonTexture& textureData = ExitButtonTexture::GetInstace();

	// 画像描画のコンポーネントを作成
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);

	// スタートボタンの動きのコンポーネントを作成
	ExitButtonMove* exitButtonMove = new ExitButtonMove(twoDimentionSprite, textureData.GetRect());
	AddComponent(exitButtonMove);
}
