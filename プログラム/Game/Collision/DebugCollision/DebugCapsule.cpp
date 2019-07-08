//--------------------------------------------------------------------------------------
// File: DebugCapsule.cpp
//
// デバッグカプセルを描画するクラス
//
// Date: 2018.6.19
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "../../../pch.h"
#include "DebugCapsule.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#ifdef _DEBUG

#include "../../../VertexShader.inc"	// 頂点シェーダー
#include "../../../PixelShader.inc"	// ピクセルシェーダー
#include "DebugCapsule.inc"	// モデルの頂点とインデックス情報

#endif

/*********************************************************************
* 関数名	: RotationArc
* 内容		: 最小弧クオータニオンを求める
* 種類		: ローカル関数
* 作成者	: 今瀬 秀康
* 作成日	: 2006/11/13
* コメント	: GAME PROGRAMING Gems 1 208P参照
*			: この関数は q * V0 = V1 を満たすクォータニオンqを返す
*--------------------------------------------------------------------
* 引数		: *q [OUT] 出力先
*			: V0 [IN] ベクトルV0
*			: V1 [IN] ベクトルV1
* 返り値	: 出力先へのポインタ
*********************************************************************/
static void RotationArc(Quaternion *q, const Vector3& V0, const Vector3& V1)
{
	Vector3 v0 = V0;
	Vector3 v1 = V1;

	v0.Normalize();
	v1.Normalize();
	Vector3 c = v0.Cross(v1);
	float d = v0.Dot(v1);
	// 回転軸が定まらないため強制的に回転クォータニオンを作成する
	if (fabsf(1.0f + d) < FLT_EPSILON)
	{
		q->x = 1.0f;
		q->y = q->z = q->w = 0.0f;
		return;
	}
	float s = sqrtf((1 + d) * 2.0f);
	q->x = c.x / s;
	q->y = c.y / s;
	q->z = c.z / s;
	q->w = s / 2.0f;
}

DebugCapsule::DebugCapsule(ID3D11Device * device, DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, float radius)
{
	SetCenterSegment(a, b);
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
	device->CreateBuffer(&desc, &data, m_vertexBuffer[0].GetAddressOf());

	// 頂点バッファの作成（ヘッド）
	desc.ByteWidth = sizeof(XMFLOAT3) * VERTEX_CNT_HEAD;
	data.pSysMem = vertexes_head;
	device->CreateBuffer(&desc, &data, m_vertexBuffer[1].GetAddressOf());

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
	device->CreateBuffer(&desc, &data, m_indexBuffer[0].GetAddressOf());

	// インデックスバッファの作成（ヘッド）
	desc.ByteWidth = sizeof(UINT) * INDEX_CNT_HEAD;
	data.pSysMem = indexes_head;
	device->CreateBuffer(&desc, &data, m_indexBuffer[1].GetAddressOf());

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

void DebugCapsule::Draw(ID3D11DeviceContext* context, CommonStates& states, const Matrix& world, const Matrix& view, const Matrix& projection)
{

#ifdef _DEBUG

	// 深度ステンシルステートの設定
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	// ラスタライズステートを設定
	context->RSSetState(m_rasterizerState.Get());

	// 頂点バッファ
	UINT vb_slot = 0;
	ID3D11Buffer* vb[2] = { m_vertexBuffer[0].Get(), m_vertexBuffer[1].Get() };
	UINT stride[1] = { sizeof(XMFLOAT3) };
	UINT offset[1] = { 0 };
	context->IASetVertexBuffers(vb_slot, 1, &vb[0], stride, offset);

	// インデックスバッファ
	context->IASetIndexBuffer(m_indexBuffer[0].Get(), DXGI_FORMAT_R32_UINT, 0);

	// トポロジー（三角形リスト）
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 入力レイアウト
	context->IASetInputLayout(m_inputLayout.Get());

	//-----------------------------------------------------------------------------------//

	Matrix WVP = m_scale * m_rotate * m_trans * world * view * projection;
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

	// メッシュの描画（ヘッド）
	WVP = m_scale_head * m_rotate * m_trans_head * world * view * projection;
	cbuff.worldViewProjection = DirectX::XMMatrixTranspose(WVP);
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->VSSetConstantBuffers(0, 1, cb);
	context->IASetVertexBuffers(vb_slot, 1, &vb[1], stride, offset);
	context->IASetIndexBuffer(m_indexBuffer[1].Get(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(INDEX_CNT_HEAD, 0, 0);

	// メッシュの描画（ヘッド）
	WVP = m_scale_head * m_rotate_head * m_trans * world * view * projection;
	cbuff.worldViewProjection = DirectX::XMMatrixTranspose(WVP);
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->VSSetConstantBuffers(0, 1, cb);
	context->DrawIndexed(INDEX_CNT_HEAD, 0, 0);

#endif

}

void DebugCapsule::SetCenterSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b)
{
	m_a = a;
	m_b = b;
	Vector3 v = b - a;
	m_trans = Matrix::CreateTranslation(m_a);
	m_trans_head = Matrix::CreateTranslation(m_b);
	m_scale = Matrix::CreateScale(m_radius, v.Length(), m_radius);
	Quaternion q;
	RotationArc(&q, Vector3(0.0f, 1.0f, 0.0f), v);
	m_rotate = Matrix::CreateFromQuaternion(q);
	m_rotate_head = Matrix::CreateRotationZ(XM_PI) * m_rotate;
}

void DebugCapsule::SetRadius(float radius)
{
	m_radius = radius;
	Vector3 v = m_b - m_a;
	m_scale = Matrix::CreateScale(m_radius, v.Length(), m_radius);
	m_scale_head = Matrix::CreateScale(m_radius);
}

void DebugCapsule::GetCenterSegment(DirectX::SimpleMath::Vector3 * a, DirectX::SimpleMath::Vector3 * b)
{
	*a = m_a;
	*b = m_b;
}

float DebugCapsule::GetRadius()
{
	return m_radius;
}
