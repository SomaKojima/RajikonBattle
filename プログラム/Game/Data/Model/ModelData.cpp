#include "../../../pch.h"
#include "ModelData.h"   
#include <wchar.h>
#include <codecvt>

using namespace DirectX;

ID3D11Device* ModelData::device = nullptr;
const std::wstring ModelData::filePath = L"Resources\\Models\\";

/// <summary>
/// モデルのコンストラクタ
/// </summary>
ModelData::ModelData()
	:
	m_model(nullptr)
{
}

/// <summary>
/// モデルのデストラクタ
/// </summary>
ModelData::~ModelData()
{
	m_model.reset();
}

void ModelData::LoadModel(std::wstring name)
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + name;
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// モデル＜車のボディ＞のコンストラクタ
/// </summary>
CarBodyModel::CarBodyModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"car.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// モデル＜車の砲台＞のコンストラクタ
/// </summary>
CarCannonModel::CarCannonModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"car_cannon.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// モデル＜部屋＞のコンストラクタ
/// </summary>
RoomModel::RoomModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"stadium.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// モデル＜弾＞のコンストラクタ
/// </summary>
BulletModel::BulletModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"bullet.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// モデル＜スカイドーム＞のコンストラクタ
/// </summary>
SkyDomeModel::SkyDomeModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"skydome.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}
