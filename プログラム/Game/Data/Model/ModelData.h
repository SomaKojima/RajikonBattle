#pragma once
#include "../../Utility/Singleton.h"

/// <summary>
/// モデルデータ
/// </summary>
class ModelData
{
public:
	static ID3D11Device* device;
	static const std::wstring filePath;

public:
	// コンストラクタ
	ModelData();
	// デストラクタ
	virtual ~ModelData();

	void LoadModel(std::wstring name);

public:
	DirectX::Model* GetModel() { return m_model.get(); }
	static void SetDevice(ID3D11Device* _device) { device = _device; }

protected:
	std::unique_ptr<DirectX::Model> m_model; 
};

/// <summary>
/// 車のモデル
/// </summary>
class CarBodyModel : public ModelData, public Singleton<CarBodyModel>
{
public:
	// コンストラクタ
	CarBodyModel();
};

/// <summary>
/// 車の大砲のモデル
/// </summary>
class CarCannonModel : public ModelData, public Singleton<CarCannonModel>
{
public:
	// コンストラクタ
	CarCannonModel();
};


/// <summary>
/// 部屋のモデル
/// </summary>
class RoomModel : public ModelData, public Singleton<RoomModel>
{
public:
	// コンストラクタ
	RoomModel();
};

/// <summary>
/// 弾のモデル
/// </summary>
class BulletModel : public ModelData, public Singleton<BulletModel>
{
public:
	// コンストラクタ
	BulletModel();
};

/// <summary>
/// スカイドームのモデル
/// </summary>
class SkyDomeModel : public ModelData, public Singleton<SkyDomeModel>
{
public:
	// コンストラクタ
	SkyDomeModel();
};


/// <summary>
/// タイトルのスタジアムモデル
/// </summary>
class TitleRoom : public ModelData, public Singleton<TitleRoom>
{
public:
	// コンストラクタ
	TitleRoom()
	{
		LoadModel(L"titleStadium.cmo");
	}
};