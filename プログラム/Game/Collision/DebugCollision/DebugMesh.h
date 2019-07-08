//--------------------------------------------------------------------------------------
// File: CollisionMesh.h
//
// Obj�`���̃��b�V�����R���W�����ɂ���N���X
//
// Date: 2018.7.11
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../Collision.h"

class DebugMesh
{
protected:

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// ��]
	DirectX::SimpleMath::Quaternion m_rotation;

private:

	// �R���W�����p�O�p�`�f�[�^
	std::vector<MyCollisionObject::Triangle> m_triangles;

	// �C���f�b�N�X��
	int m_indexCnt;

	struct ConstantBuffer
	{
		DirectX::XMMATRIX worldViewProjection;
	};

	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;

	// ���X�^���C�U�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �R���W�����p�O�p�`�f�[�^�̒ǉ��֐�
	//void AddTriangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c);

	// �`��
	void Draw(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

public:
	// �R���X�g���N�^
	DebugMesh(ID3D11Device* device, wchar_t* fname);

	// �ʒu��ݒ肷��֐�
	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	// ��]��ݒ肷��֐�
	void SetRotation(DirectX::SimpleMath::Quaternion rotation) { m_rotation = rotation; }

	// �f�o�b�O�p�R���W�����\���֐�
	void DrawCollision(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// ���b�V���̎O�p�`�|���S���̐����擾����֐�
	int GetTriangleCnt();

	// �w��C���f�b�N�X�̃R���W�����p�O�p�`�f�[�^���擾����֐�
	//const Collision::Triangle& GetTriangle(int id);

	// �����Ƃ̌�������֐�
	//bool HitCheck_Segment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, int* id, DirectX::SimpleMath::Vector3* hit_pos);
};