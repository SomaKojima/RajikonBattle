#include "../../../pch.h"
#include "ModelData.h"   
#include <wchar.h>
#include <codecvt>

using namespace DirectX;

ID3D11Device* ModelData::device = nullptr;
const std::wstring ModelData::filePath = L"Resources\\Models\\";

/// <summary>
/// ���f���̃R���X�g���N�^
/// </summary>
ModelData::ModelData()
	:
	m_model(nullptr)
{
}

/// <summary>
/// ���f���̃f�X�g���N�^
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
/// ���f�����Ԃ̃{�f�B���̃R���X�g���N�^
/// </summary>
CarBodyModel::CarBodyModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"car.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// ���f�����Ԃ̖C�䁄�̃R���X�g���N�^
/// </summary>
CarCannonModel::CarCannonModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"car_cannon.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// ���f�����������̃R���X�g���N�^
/// </summary>
RoomModel::RoomModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"stadium.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// ���f�����e���̃R���X�g���N�^
/// </summary>
BulletModel::BulletModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"bullet.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}

/// <summary>
/// ���f�����X�J�C�h�[�����̃R���X�g���N�^
/// </summary>
SkyDomeModel::SkyDomeModel()
{
	EffectFactory fx(device);
	fx.SetDirectory(filePath.c_str());
	std::wstring path = filePath + L"skydome.cmo";
	m_model = Model::CreateFromCMO(device, path.c_str(), fx);
}
