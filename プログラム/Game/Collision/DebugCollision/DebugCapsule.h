//--------------------------------------------------------------------------------------
// File: DebugCapsule.h
//
// �f�o�b�O�J�v�Z����`�悷��N���X
//
// Date: 2018.6.19
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

class DebugCapsule
{
	struct ConstantBuffer
	{
		DirectX::XMMATRIX worldViewProjection;
	};

	// ���ԕ��̐����̊J�n�_
	DirectX::SimpleMath::Vector3 m_a;

	// ���ԕ��̐����̏I���_
	DirectX::SimpleMath::Vector3 m_b;

	// ���a
	float m_radius;

	// ���s�ړ��s��
	DirectX::SimpleMath::Matrix m_trans;
	DirectX::SimpleMath::Matrix m_trans_head;

	// �X�P�[���s��
	DirectX::SimpleMath::Matrix m_scale;
	DirectX::SimpleMath::Matrix m_scale_head;

	// ��]�s��
	DirectX::SimpleMath::Matrix m_rotate;
	DirectX::SimpleMath::Matrix m_rotate_head;

	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;

	// ���X�^���C�U�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer[2];

	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer[2];

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

public:
	// �R���X�g���N�^
	DebugCapsule(ID3D11Device* device, DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, float radius);

	// �f�o�b�O�J�v�Z���̕`��֐�
	void Draw(ID3D11DeviceContext* context, DirectX::CommonStates& states, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// �f�o�b�O�J�v�Z���̒��ԕ��̐����̐ݒ�֐�
	void SetCenterSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b);

	// �f�o�b�O�X�t�B�A�̔��a�̐ݒ�֐�
	void SetRadius(float radius);

	// �f�o�b�O�X�t�B�A�̃Z���^�[�̎擾�֐�
	void GetCenterSegment(DirectX::SimpleMath::Vector3* a, DirectX::SimpleMath::Vector3* b);

	// �f�o�b�O�X�t�B�A�̔��a�̎擾�֐�
	float GetRadius();

};
