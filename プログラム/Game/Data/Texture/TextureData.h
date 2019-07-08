#pragma once
#include "../../Utility/Singleton.h"
#include <list>

/// <summary>
/// �摜�f�[�^
/// </summary>
class TextureData
{
public:
	static ID3D11Device* device;
	static const std::wstring filePath;

public:
	// �R���X�g���N�^
	TextureData();
	// �f�X�g���N�^
	virtual ~TextureData();

public:
	/// <summary>
	/// �֐�
	/// </summary>
	
protected:
	// �摜�̓ǂݍ���
	void LoadTexture(std::wstring name);

public:
	/// <summary>
	/// �A�N�Z�T��
	/// </summary>
	static void SetDevice(ID3D11Device* _device) { device = _device; }

	ID3D11ShaderResourceView* GetTexture() { return m_texture.Get(); }
	const D3D11_TEXTURE2D_DESC& GetDesc() { return m_desc; }
	int GetWidth() { return m_desc.Width; }
	int GetHeight() { return m_desc.Height; }
	RECT GetRect() { return RECT{ 0, 0, static_cast<int>(m_desc.Width), static_cast<int>(m_desc.Height) }; }

protected:
	/// <summary>
	/// �����o�ϐ�
	/// </summary>
	

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	D3D11_TEXTURE2D_DESC m_desc;
};

/// <summary>
/// �摜���^�C�g�����S��
/// </summary>
class TitleLogoTexture : public TextureData, public Singleton<TitleLogoTexture>
{
public:
	// �R���X�g���N�^
	TitleLogoTexture()
	{
		LoadTexture(L"title_rajibato.png");
	}
};

/// <summary>
/// �摜���X�^�[�g�{�^����
/// </summary>
class StartButtonTexture : public TextureData, public Singleton<StartButtonTexture>
{
public:
	// �R���X�g���N�^
	StartButtonTexture()
	{
		LoadTexture(L"StartButton.png");
	}
};


/// <summary>
/// �摜���I���{�^����
/// </summary>
class ExitButtonTexture : public TextureData, public Singleton<ExitButtonTexture>
{
public:
	// �R���X�g���N�^
	ExitButtonTexture()
	{
		LoadTexture(L"ExitButton.png");
	}
};


/// <summary>
/// �摜���X�^�[�g�{�^���F������
/// </summary>
class StartButtonStrTexture : public TextureData, public Singleton<StartButtonStrTexture>
{
public:
	// �R���X�g���N�^
	StartButtonStrTexture()
	{
		LoadTexture(L"StartButton_str.png");
	}
};


/// <summary>
/// �摜���X�^�[�g�{�^���F�w�i��
/// </summary>
class StartButtonBGTexture : public TextureData, public Singleton<StartButtonBGTexture>
{
public:
	// �R���X�g���N�^
	StartButtonBGTexture()
	{
		LoadTexture(L"StartButton_background.png");
	}
};

/// <summary>
/// �摜�����S��
/// </summary>
class LogoTexture : public TextureData, public Singleton<LogoTexture>
{
public:
	// �R���X�g���N�^
	LogoTexture()
	{
		LoadTexture(L"Logo.png");
	}
};

/// <summary>
/// �摜��������
/// </summary>
class NumTexture : public TextureData, public Singleton<NumTexture>
{
public:
	// �R���X�g���N�^
	NumTexture()
	{
		LoadTexture(L"Num.png");
	}
};


/// <summary>
/// �摜�����e�B�N����
/// </summary>
class ReticuleTexture : public TextureData, public Singleton<ReticuleTexture>
{
public:
	// �R���X�g���N�^
	ReticuleTexture()
	{
		LoadTexture(L"Reticule.png");
	}
};


/// <summary>
/// �摜��HPBarFlame��
/// </summary>
class HPBarFlameTexture : public TextureData, public Singleton<HPBarFlameTexture>
{
public:
	// �R���X�g���N�^
	HPBarFlameTexture()
	{
		LoadTexture(L"HPBarFlame.png");
	}
};


/// <summary>
/// �摜��HPBarGreen��
/// </summary>
class HPBarGreenTexture : public TextureData, public Singleton<HPBarGreenTexture>
{
public:
	// �R���X�g���N�^
	HPBarGreenTexture()
	{
		LoadTexture(L"HPBarGreen.png");
	}
};

/// <summary>
/// �摜��HPBarStrPlayer��
/// </summary>
class HPBarStrPlayerTexture : public TextureData, public Singleton<HPBarStrPlayerTexture>
{
public:
	// �R���X�g���N�^
	HPBarStrPlayerTexture()
	{
		LoadTexture(L"HPBarStrPlayer.png");
	}
};


/// <summary>
/// �摜��HPBarStrEnemy��
/// </summary>
class HPBarStrEnemyTexture : public TextureData, public Singleton<HPBarStrEnemyTexture>
{
public:
	// �R���X�g���N�^
	HPBarStrEnemyTexture()
	{
		LoadTexture(L"HPBarStrEnemy.png");
	}
};


/// <summary>
/// �摜��npcWin��
/// </summary>
class NPCWinTexture : public TextureData, public Singleton<NPCWinTexture>
{
public:
	// �R���X�g���N�^
	NPCWinTexture()
	{
		LoadTexture(L"npcWin.png");
	}
};


/// <summary>
/// �摜��YouWin��
/// </summary>
class YouWinTexture : public TextureData, public Singleton<YouWinTexture>
{
public:
	// �R���X�g���N�^
	YouWinTexture()
	{
		LoadTexture(L"youWin.png");
	}
};


/// <summary>
/// �摜��TimeUp��
/// </summary>
class TimeUpTexture : public TextureData, public Singleton<TimeUpTexture>
{
public:
	// �R���X�g���N�^
	TimeUpTexture()
	{
		LoadTexture(L"TimeUp.png");
	}
};
