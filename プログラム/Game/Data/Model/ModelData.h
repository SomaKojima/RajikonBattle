#pragma once
#include "../../Utility/Singleton.h"

/// <summary>
/// ���f���f�[�^
/// </summary>
class ModelData
{
public:
	static ID3D11Device* device;
	static const std::wstring filePath;

public:
	// �R���X�g���N�^
	ModelData();
	// �f�X�g���N�^
	virtual ~ModelData();

	void LoadModel(std::wstring name);

public:
	DirectX::Model* GetModel() { return m_model.get(); }
	static void SetDevice(ID3D11Device* _device) { device = _device; }

protected:
	std::unique_ptr<DirectX::Model> m_model; 
};

/// <summary>
/// �Ԃ̃��f��
/// </summary>
class CarBodyModel : public ModelData, public Singleton<CarBodyModel>
{
public:
	// �R���X�g���N�^
	CarBodyModel();
};

/// <summary>
/// �Ԃ̑�C�̃��f��
/// </summary>
class CarCannonModel : public ModelData, public Singleton<CarCannonModel>
{
public:
	// �R���X�g���N�^
	CarCannonModel();
};


/// <summary>
/// �����̃��f��
/// </summary>
class RoomModel : public ModelData, public Singleton<RoomModel>
{
public:
	// �R���X�g���N�^
	RoomModel();
};

/// <summary>
/// �e�̃��f��
/// </summary>
class BulletModel : public ModelData, public Singleton<BulletModel>
{
public:
	// �R���X�g���N�^
	BulletModel();
};

/// <summary>
/// �X�J�C�h�[���̃��f��
/// </summary>
class SkyDomeModel : public ModelData, public Singleton<SkyDomeModel>
{
public:
	// �R���X�g���N�^
	SkyDomeModel();
};


/// <summary>
/// �^�C�g���̃X�^�W�A�����f��
/// </summary>
class TitleRoom : public ModelData, public Singleton<TitleRoom>
{
public:
	// �R���X�g���N�^
	TitleRoom()
	{
		LoadModel(L"titleStadium.cmo");
	}
};