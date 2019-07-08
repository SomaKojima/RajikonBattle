#include "../../../pch.h"
#include "ResultStr.h"
#include "../../Component/Render/TwoDimentionSprite.h"
#include "../../Data/Texture/TextureData.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultStr::ResultStr()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ResultStr::~ResultStr()
{
}

/// <summary>
/// 生成
/// </summary>
void ResultStr::Instance(Type type)
{
	// 画像描画のコンポーネントを作成
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
