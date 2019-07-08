#pragma once
#include "../../Utility/Singleton.h"
#include <list>

/// <summary>
/// 画像データ
/// </summary>
class TextureData
{
public:
	static ID3D11Device* device;
	static const std::wstring filePath;

public:
	// コンストラクタ
	TextureData();
	// デストラクタ
	virtual ~TextureData();

public:
	/// <summary>
	/// 関数
	/// </summary>
	
protected:
	// 画像の読み込み
	void LoadTexture(std::wstring name);

public:
	/// <summary>
	/// アクセサリ
	/// </summary>
	static void SetDevice(ID3D11Device* _device) { device = _device; }

	ID3D11ShaderResourceView* GetTexture() { return m_texture.Get(); }
	const D3D11_TEXTURE2D_DESC& GetDesc() { return m_desc; }
	int GetWidth() { return m_desc.Width; }
	int GetHeight() { return m_desc.Height; }
	RECT GetRect() { return RECT{ 0, 0, static_cast<int>(m_desc.Width), static_cast<int>(m_desc.Height) }; }

protected:
	/// <summary>
	/// メンバ変数
	/// </summary>
	

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	D3D11_TEXTURE2D_DESC m_desc;
};

/// <summary>
/// 画像＜タイトルロゴ＞
/// </summary>
class TitleLogoTexture : public TextureData, public Singleton<TitleLogoTexture>
{
public:
	// コンストラクタ
	TitleLogoTexture()
	{
		LoadTexture(L"title_rajibato.png");
	}
};

/// <summary>
/// 画像＜スタートボタン＞
/// </summary>
class StartButtonTexture : public TextureData, public Singleton<StartButtonTexture>
{
public:
	// コンストラクタ
	StartButtonTexture()
	{
		LoadTexture(L"StartButton.png");
	}
};


/// <summary>
/// 画像＜終了ボタン＞
/// </summary>
class ExitButtonTexture : public TextureData, public Singleton<ExitButtonTexture>
{
public:
	// コンストラクタ
	ExitButtonTexture()
	{
		LoadTexture(L"ExitButton.png");
	}
};


/// <summary>
/// 画像＜スタートボタン：文字＞
/// </summary>
class StartButtonStrTexture : public TextureData, public Singleton<StartButtonStrTexture>
{
public:
	// コンストラクタ
	StartButtonStrTexture()
	{
		LoadTexture(L"StartButton_str.png");
	}
};


/// <summary>
/// 画像＜スタートボタン：背景＞
/// </summary>
class StartButtonBGTexture : public TextureData, public Singleton<StartButtonBGTexture>
{
public:
	// コンストラクタ
	StartButtonBGTexture()
	{
		LoadTexture(L"StartButton_background.png");
	}
};

/// <summary>
/// 画像＜ロゴ＞
/// </summary>
class LogoTexture : public TextureData, public Singleton<LogoTexture>
{
public:
	// コンストラクタ
	LogoTexture()
	{
		LoadTexture(L"Logo.png");
	}
};

/// <summary>
/// 画像＜数字＞
/// </summary>
class NumTexture : public TextureData, public Singleton<NumTexture>
{
public:
	// コンストラクタ
	NumTexture()
	{
		LoadTexture(L"Num.png");
	}
};


/// <summary>
/// 画像＜レティクル＞
/// </summary>
class ReticuleTexture : public TextureData, public Singleton<ReticuleTexture>
{
public:
	// コンストラクタ
	ReticuleTexture()
	{
		LoadTexture(L"Reticule.png");
	}
};


/// <summary>
/// 画像＜HPBarFlame＞
/// </summary>
class HPBarFlameTexture : public TextureData, public Singleton<HPBarFlameTexture>
{
public:
	// コンストラクタ
	HPBarFlameTexture()
	{
		LoadTexture(L"HPBarFlame.png");
	}
};


/// <summary>
/// 画像＜HPBarGreen＞
/// </summary>
class HPBarGreenTexture : public TextureData, public Singleton<HPBarGreenTexture>
{
public:
	// コンストラクタ
	HPBarGreenTexture()
	{
		LoadTexture(L"HPBarGreen.png");
	}
};

/// <summary>
/// 画像＜HPBarStrPlayer＞
/// </summary>
class HPBarStrPlayerTexture : public TextureData, public Singleton<HPBarStrPlayerTexture>
{
public:
	// コンストラクタ
	HPBarStrPlayerTexture()
	{
		LoadTexture(L"HPBarStrPlayer.png");
	}
};


/// <summary>
/// 画像＜HPBarStrEnemy＞
/// </summary>
class HPBarStrEnemyTexture : public TextureData, public Singleton<HPBarStrEnemyTexture>
{
public:
	// コンストラクタ
	HPBarStrEnemyTexture()
	{
		LoadTexture(L"HPBarStrEnemy.png");
	}
};


/// <summary>
/// 画像＜npcWin＞
/// </summary>
class NPCWinTexture : public TextureData, public Singleton<NPCWinTexture>
{
public:
	// コンストラクタ
	NPCWinTexture()
	{
		LoadTexture(L"npcWin.png");
	}
};


/// <summary>
/// 画像＜YouWin＞
/// </summary>
class YouWinTexture : public TextureData, public Singleton<YouWinTexture>
{
public:
	// コンストラクタ
	YouWinTexture()
	{
		LoadTexture(L"youWin.png");
	}
};


/// <summary>
/// 画像＜TimeUp＞
/// </summary>
class TimeUpTexture : public TextureData, public Singleton<TimeUpTexture>
{
public:
	// コンストラクタ
	TimeUpTexture()
	{
		LoadTexture(L"TimeUp.png");
	}
};
