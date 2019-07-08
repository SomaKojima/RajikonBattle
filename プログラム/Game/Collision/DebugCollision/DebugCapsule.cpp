//--------------------------------------------------------------------------------------
// File: DebugCapsule.cpp
//
// �f�o�b�O�J�v�Z����`�悷��N���X
//
// Date: 2018.6.19
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "../../../pch.h"
#include "DebugCapsule.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#ifdef _DEBUG

#include "../../../VertexShader.inc"	// ���_�V�F�[�_�[
#include "../../../PixelShader.inc"	// �s�N�Z���V�F�[�_�[
#include "DebugCapsule.inc"	// ���f���̒��_�ƃC���f�b�N�X���

#endif

/*********************************************************************
* �֐���	: RotationArc
* ���e		: �ŏ��ʃN�I�[�^�j�I�������߂�
* ���		: ���[�J���֐�
* �쐬��	: ���� �G�N
* �쐬��	: 2006/11/13
* �R�����g	: GAME PROGRAMING Gems 1 208P�Q��
*			: ���̊֐��� q * V0 = V1 �𖞂����N�H�[�^�j�I��q��Ԃ�
*--------------------------------------------------------------------
* ����		: *q [OUT] �o�͐�
*			: V0 [IN] �x�N�g��V0
*			: V1 [IN] �x�N�g��V1
* �Ԃ�l	: �o�͐�ւ̃|�C���^
*********************************************************************/
static void RotationArc(Quaternion *q, const Vector3& V0, const Vector3& V1)
{
	Vector3 v0 = V0;
	Vector3 v1 = V1;

	v0.Normalize();
	v1.Normalize();
	Vector3 c = v0.Cross(v1);
	float d = v0.Dot(v1);
	// ��]������܂�Ȃ����ߋ����I�ɉ�]�N�H�[�^�j�I�����쐬����
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
	device->CreateBuffer(&desc, &data, m_vertexBuffer[0].GetAddressOf());

	// ���_�o�b�t�@�̍쐬�i�w�b�h�j
	desc.ByteWidth = sizeof(XMFLOAT3) * VERTEX_CNT_HEAD;
	data.pSysMem = vertexes_head;
	device->CreateBuffer(&desc, &data, m_vertexBuffer[1].GetAddressOf());

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
	device->CreateBuffer(&desc, &data, m_indexBuffer[0].GetAddressOf());

	// �C���f�b�N�X�o�b�t�@�̍쐬�i�w�b�h�j
	desc.ByteWidth = sizeof(UINT) * INDEX_CNT_HEAD;
	data.pSysMem = indexes_head;
	device->CreateBuffer(&desc, &data, m_indexBuffer[1].GetAddressOf());

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

void DebugCapsule::Draw(ID3D11DeviceContext* context, CommonStates& states, const Matrix& world, const Matrix& view, const Matrix& projection)
{

#ifdef _DEBUG

	// �[�x�X�e���V���X�e�[�g�̐ݒ�
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	// ���X�^���C�Y�X�e�[�g��ݒ�
	context->RSSetState(m_rasterizerState.Get());

	// ���_�o�b�t�@
	UINT vb_slot = 0;
	ID3D11Buffer* vb[2] = { m_vertexBuffer[0].Get(), m_vertexBuffer[1].Get() };
	UINT stride[1] = { sizeof(XMFLOAT3) };
	UINT offset[1] = { 0 };
	context->IASetVertexBuffers(vb_slot, 1, &vb[0], stride, offset);

	// �C���f�b�N�X�o�b�t�@
	context->IASetIndexBuffer(m_indexBuffer[0].Get(), DXGI_FORMAT_R32_UINT, 0);

	// �g�|���W�[�i�O�p�`���X�g�j
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ���̓��C�A�E�g
	context->IASetInputLayout(m_inputLayout.Get());

	//-----------------------------------------------------------------------------------//

	Matrix WVP = m_scale * m_rotate * m_trans * world * view * projection;
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

	// ���b�V���̕`��i�w�b�h�j
	WVP = m_scale_head * m_rotate * m_trans_head * world * view * projection;
	cbuff.worldViewProjection = DirectX::XMMatrixTranspose(WVP);
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);
	context->VSSetConstantBuffers(0, 1, cb);
	context->IASetVertexBuffers(vb_slot, 1, &vb[1], stride, offset);
	context->IASetIndexBuffer(m_indexBuffer[1].Get(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(INDEX_CNT_HEAD, 0, 0);

	// ���b�V���̕`��i�w�b�h�j
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
