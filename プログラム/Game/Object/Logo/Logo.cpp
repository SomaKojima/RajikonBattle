#include "../../../pch.h"
#include "Logo.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"
#include "../../Component/Object/Logo/LogoMove.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Logo::Logo()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Logo::~Logo()
{
}

/// <summary>
/// 生成
/// </summary>
void Logo::Instance()
{
	// 画像のデータを取得する
	TextureData& textureData = LogoTexture::GetInstace();
	RECT rect = textureData.GetRect();

	// ----- ウィンドウの長方形(Rectangle)の情報を取得する
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int wwidth = (wRect.right - wRect.left);
	int wheight = (wRect.bottom - wRect.top);

	float scaleX = wwidth / (float)(rect.right / 5);
	float scaleY = wheight / (float)(rect.bottom / 5);

	// 画像描画のコンポーネントを作成
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	twoDimentionSprite->SetOrigin(Vector2::Zero);
	twoDimentionSprite->SetScale(Vector2(scaleX, scaleY));
	AddComponent(twoDimentionSprite);
	
	// ロゴの動きのコンポーネントを作成
	LogoMove* logoMove = new LogoMove(twoDimentionSprite, textureData.GetRect());
	AddComponent(logoMove);
}
