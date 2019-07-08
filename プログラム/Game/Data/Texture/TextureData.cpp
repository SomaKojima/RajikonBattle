#include "../../pch.h"
#include "TextureData.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ID3D11Device* TextureData::device = nullptr;
const std::wstring TextureData::filePath = L"Resources\\Textures\\";

/// <summary>
/// �摜�f�[�^�̃R���X�g���N�^
/// </summary>
TextureData::TextureData()
	:
	m_texture(nullptr)
{
}

/// <summary>
/// �摜�f�[�^�̃f�X�g���N�^
/// </summary>
TextureData::~TextureData()
{
	m_texture.Reset();
}

/// <summary>
/// �摜�̓ǂݍ���
/// </summary>
/// <param name="name"></param>
void TextureData::LoadTexture(std::wstring name)
{
	// �e�N�X�`���̃��[�h 
	std::wstring path = filePath + name;
	ID3D11Resource* resource = nullptr;
	HRESULT hr = CreateWICTextureFromFile(device, path.c_str(), &resource, m_texture.GetAddressOf());
	DX::ThrowIfFailed(hr);

	// ���\�[�X�̏����擾
	ID3D11Texture2D* texture2d = static_cast<ID3D11Texture2D*>(resource);
	texture2d->GetDesc(&m_desc);
	resource->Release();
}
