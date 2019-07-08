//--------------------------------------------------------------------------------------
// File: DebugSphere.cpp
//
// デバッグスフィアを描画するクラス
//
// Date: 2018.6.4
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "../../../pch.h"
#include "DebugSphere.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#ifdef _DEBUG

#include "../../../VertexShader.inc"	// 頂点シェーダー
#include "../../../PixelShader.inc"	// ピクセルシェーダー
#include "DebugSphere.inc"	// モデルの頂点とインデックス情報

#endif

DebugSphere::DebugSphere(ID3D11Device* device, Vector3 center, float radius)
	: m_center(Vector3(0.0f, 0.0f, 0.0f))
{
	SetCenter(center);
	SetRadius(radius);

#ifdef _DEBUG

	// 頂点バッファの作成
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(XMFLOAT3) * VERTEX_CNT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	 // 頂点バッファ
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	// 頂点の設定
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertexes;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// 頂点バッファの作成
	device->CreateBuffer(&desc, &data, m_vertexBuffer.GetAddressOf());

	// インデックスバッファの作成
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * INDEX_CNT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;	// インデックスバッファ
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	// インデックスの設定
	data.pSysMem = indexes;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// インデックスバッファの作成
	device->CreateBuffer(&desc, &data, m_indexBuffer.GetAddressOf());

	// 定数バッファの作成
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstantBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, NULL, m_constantBuffer.GetAddressOf());

	// シェーダーの作成
	device->CreateVertexShader((void*)VertexShader, sizeof(VertexShader), NULL, m_vertexShader.GetAddressOf());
	device->CreatePixelShader((void*)PixelShader, sizeof(PixelShader), NULL, m_pixelShader.GetAddressOf());

	// 入力レイアウトの作成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(layout, _countof(layout), VertexShader, sizeof(VertexShader) / sizeof(BYTE), m_inputLayout.GetAddressOf());

	// 深度ステンシルステートの作成
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	dsDesc.StencilEnable = FALSE;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	device->CreateDepthStencilState(&dsDesc, m_depthStencilState.GetAddressOf());

	// ラスタライザステートの作成
	D3D11_RASTERIZER_DESC rsDesc;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.FrontCounterClockwise = FALSE;
	rsDesc.DepthBias = 0;
	rsDesc.DepthBiasClamp = 0;
	rsDesc.SlopeScaledDepthBias = 0;
	rsDesc.DepthClipEnable = FALSE;
	rsDesc.ScissorEnable = FALSE;
	rsDesc.MultisampleEnable = FALSE;
	rsDesc.AntialiasedLineEnable = FALSE;
	device->CreateRasterizerState(&rsDesc, m_rasterizerState.GetAddressOf());
#endif

}

void DebugSphere::Draw(ID3D11DeviceContext* context, CommonStates& states, const Matrix& world, const Matrix& view, const Matrix& projection)
{

#ifdef _DEBUG

	// 深度ステンシルステートの設定
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	// ラスタライズステートを設定
	context->RSSetState(m_rasterizerState.Get());

	// 頂点バッファ
	UINT vb_slot = 0;
	ID3D11Buffer* vb[1] = { m_vertexBuffer.Get() };
	UINT stride[1] = { sizeof(XMFLOAT3) };
	UINT offset[1] = { 0 };
	context->IASetVertexBuffers(vb_slot, 1, vb, stride, offset);

	// インデックスバッファ
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// トポロジー（三角形リスト）
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 入力レイアウト
	context->IASetInputLayout(m_inputLayout.Get());

	//-----------------------------------------------------------------------------------//

	Matrix WVP = m_scale * m_trans * world * view * projection;
	ConstantBuffer cbuff;
	cbuff.worldViewProjection = DirectX::XMMatrixTranspose(WVP);
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// 定数バッファ
	ID3D11Buffer* cb[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);

	//-----------------------------------------------------------------------------------//

	// シェーダを設定
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//-----------------------------------------------------------------------------------//

	// メッシュの描画
	context->DrawIndexed(INDEX_CNT, 0, 0);

#endif

}

void DebugSphere::SetCenter(DirectX::SimpleMath::Vector3 center)
{
	m_center = center;
	m_trans = Matrix::CreateTranslation(m_center);
}

DirectX::SimpleMath::Vector3 DebugSphere::GetCenter()
{
	return m_center;
}

void DebugSphere::SetRadius(float radius)
{
	m_radius = radius;
	m_scale = Matrix::CreateScale(m_radius);
}

float DebugSphere::GetRadius()
{
	return m_radius;
}
