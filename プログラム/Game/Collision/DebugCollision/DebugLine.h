//--------------------------------------------------------------------------------------
// File: DebugLine.h
//
// �f�o�b�O���C����`�悷��N���X
//
// Date: 2018.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

class DebugLine
{
	struct Line
	{
		DirectX::SimpleMath::Vector3 p;	// �X�^�[�g�ʒu
		DirectX::SimpleMath::Vector3 d;	// �����x�N�g��
		DirectX::XMFLOAT4 color;		// �F
	};

	// �`�悷�郉�C�����
	std::vector<Line> m_lines;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// �R�����X�e�[�g�ւ̃|�C���^
	DirectX::CommonStates* m_states;

public:
	//�R���X�g���N�^
	DebugLine(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::CommonStates* states);

	// �`��
	void Render(ID3D11DeviceContext* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// ���C���̒ǉ�
	/// </summary>
	/// <param name="p">�J�n�ʒu</param>
	/// <param name="d">�x�N�g��</param>
	/// <param name="color">�F</param>
	void AddLine(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 d, DirectX::GXMVECTOR color = DirectX::Colors::White);

	/// <summary>
	/// ���C���̒ǉ�
	/// </summary>
	/// <param name="a">�J�n�ʒu</param>
	/// <param name="b">�I���ʒu</param>
	/// <param name="color">�F</param>
	void AddLine_Point2Point(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::GXMVECTOR color = DirectX::Colors::White);
};

