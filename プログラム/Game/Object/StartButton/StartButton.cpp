#include "../../pch.h"
#include "StartButton.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"
#include "../../Component/Object/StartButton/StartButtonMove.h"

/// <summary>
/// コンストラクタ
/// </summary>
StartButton::StartButton()
{
}

/// <summary>
/// デストラクタ
/// </summary>
StartButton::~StartButton()
{
}

/// <summary>
/// 生成
/// </summary>
void StartButton::Instance()
{
	// 画像のデータを取得する
	StartButtonTexture& textureData = StartButtonTexture::GetInstace(); 


	TextureData& textureData1 = StartButtonStrTexture::GetInstace();
	TextureData& textureData2 = StartButtonBGTexture::GetInstace();

	// 画像描画のコンポーネントを作成
	TwoDimentionSprite* twoDimentionSprite = new TwoDimentionSprite(textureData.GetTexture(), textureData.GetRect());
	AddComponent(twoDimentionSprite);
	// スタートボタンの動きのコンポーネントを作成
	StartButtonMove* startButtonMove = new StartButtonMove(twoDimentionSprite, textureData.GetRect());
	AddComponent(startButtonMove);

	//// 画像描画のコンポーネントを作成
	//TwoDimentionSprite* twoDimentionSprite2 = new TwoDimentionSprite(textureData2.GetTexture(), textureData2.GetRect());
	//AddComponent(twoDimentionSprite2);

	//// 画像描画のコンポーネントを作成
	//TwoDimentionSprite* twoDimentionSprite1 = new TwoDimentionSprite(textureData1.GetTexture(), textureData1.GetRect());
	//AddComponent(twoDimentionSprite1);

	//// スタートボタンの動きのコンポーネントを作成
	//StartButtonMove* startButtonMove = new StartButtonMove(twoDimentionSprite2, textureData2.GetRect());
	//AddComponent(startButtonMove);
}
