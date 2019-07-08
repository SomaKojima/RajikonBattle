#include "../../pch.h"
#include "TitleLogo.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Component/Object/TitleLogo/TitleLogoMove.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleLogo::TitleLogo()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleLogo::~TitleLogo()
{
}

/// <summary>
/// 生成
/// </summary>
void TitleLogo::Instance()
{
	// 画像のデータを取得する
	TitleLogoTexture& textureData = TitleLogoTexture::GetInstace();

	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);

	TitleLogoMove* titileLogoMove = new TitleLogoMove(200.0f);
	AddComponent(titileLogoMove);
}
