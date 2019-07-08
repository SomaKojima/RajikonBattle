//--------------------------------------------------------------------------------------
// File: DebugSphere.cpp
//
// �f�o�b�O�X�t�B�A��`�悷��N���X
//
// Date: 2018.6.4
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "../../../pch.h"
#include "DebugSphere.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#ifdef _DEBUG

#include "../../../VertexShader.inc"	// ���_�V�F�[�_�[
#include "../../../PixelShader.inc"	// �s�N�Z���V�F�[�_�[
#include "DebugSphere.inc"	// ���f���̒��_�ƃC���f�b�N�X���

#endif

DebugSphere::DebugSphere(ID3D11Device* device, Vector3 center, float radius)
	: m_center(Vector3(0.0f, 0.0f, 0.0f))
{
	SetCenter(center);
	SetRadius(radius);

#ifdef _DEBUG

	// ���_�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(XMFLOAT3) * VERTEX_CNT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	 // ���_�o�b�t�@
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	// ���_�̐ݒ�
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertexes;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// ���_�o�b�t�@�̍쐬
	device->CreateBuffer(&desc, &data, m_vertexBuffer.GetAddressOf());

	// �C���f�b�N�X�o�b�t�@�̍쐬
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * INDEX_CNT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;	// �C���f�b�N�X�o�b�t�@
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	// �C���f�b�N�X�̐ݒ�
	data.pSysMem = indexes;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// �C���f�b�N�X�o�b�t�@�̍쐬
	device->CreateBuffer(&desc, &data, m_indexBuffer.GetAddressOf());

	// �萔�o�b�t�@�̍쐬
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstantBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, NULL, m_constantBuffer.GetAddressOf());

	// �V�F�[�_�[�̍쐬
	device->CreateVertexShader((void*)VertexShader, sizeof(VertexShader), NULL, m_vertexShader.GetAddressOf());
	device->CreatePixelShader((void*)PixelShader, sizeof(PixelShader), NULL, m_pixelShader.GetAddressOf());

	// ���̓��C�A�E�g�̍쐬
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(layout, _countof(layout), VertexShader, sizeof(VertexShader) / sizeof(BYTE), m_inputLayout.GetAddressOf());

	// �[�x�X�e���V���X�e�[�g�̍쐬
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

	// ���X�^���C�U�X�e�[�g�̍쐬
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

	// �[�x�X�e���V���X�e�[�g�̐ݒ�
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	// ���X�^���C�Y�X�e�[�g��ݒ�
	context->RSSetState(m_rasterizerState.Get());

	// ���_�o�b�t�@
	UINT vb_slot = 0;
	ID3D11Buffer* vb[1] = { m_vertexBuffer.Get() };
	UINT stride[1] = { sizeof(XMFLOAT3) };
	UINT offset[1] = { 0 };
	context->IASetVertexBuffers(vb_slot, 1, vb, stride, offset);

	// �C���f�b�N�X�o�b�t�@
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// �g�|���W�[�i�O�p�`���X�g�j
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ���̓��C�A�E�g
	context->IASetInputLayout(m_inputLayout.Get());

	//-----------------------------------------------------------------------------------//

	Matrix WVP = m_scale * m_trans * world * view * projection;
	ConstantBuffer cbuff;
	cbuff.worldViewProjection = DirectX::XMMatrixTranspose(WVP);
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �萔�o�b�t�@
	ID3D11Buffer* cb[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);

	//-----------------------------------------------------------------------------------//

	// �V�F�[�_��ݒ�
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//-----------------------------------------------------------------------------------//

	// ���b�V���̕`��
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
