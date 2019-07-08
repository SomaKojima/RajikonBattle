#include "../../../pch.h"
#include "Reticule.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// コンストラクタ
/// </summary>
Reticule::Reticule()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Reticule::~Reticule()
{
}

/// <summary>
/// 生成
/// </summary>
void Reticule::Instance()
{
	// 画像のデータを取得する
	ReticuleTexture& textureData = ReticuleTexture::GetInstace();
	RECT rect = textureData.GetRect();

	// 画像描画のコンポーネントを作成
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);
}
