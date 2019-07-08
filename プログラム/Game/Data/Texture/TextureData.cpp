#include "../../pch.h"
#include "TextureData.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ID3D11Device* TextureData::device = nullptr;
const std::wstring TextureData::filePath = L"Resources\\Textures\\";

/// <summary>
/// 画像データのコンストラクタ
/// </summary>
TextureData::TextureData()
	:
	m_texture(nullptr)
{
}

/// <summary>
/// 画像データのデストラクタ
/// </summary>
TextureData::~TextureData()
{
	m_texture.Reset();
}

/// <summary>
/// 画像の読み込み
/// </summary>
/// <param name="name"></param>
void TextureData::LoadTexture(std::wstring name)
{
	// テクスチャのロード 
	std::wstring path = filePath + name;
	ID3D11Resource* resource = nullptr;
	HRESULT hr = CreateWICTextureFromFile(device, path.c_str(), &resource, m_texture.GetAddressOf());
	DX::ThrowIfFailed(hr);

	// リソースの情報を取得
	ID3D11Texture2D* texture2d = static_cast<ID3D11Texture2D*>(resource);
	texture2d->GetDesc(&m_desc);
	resource->Release();
}
