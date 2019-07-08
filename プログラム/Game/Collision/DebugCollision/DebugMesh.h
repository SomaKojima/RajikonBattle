//--------------------------------------------------------------------------------------
// File: CollisionMesh.h
//
// Obj形式のメッシュをコリジョンにするクラス
//
// Date: 2018.7.11
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../Collision.h"

class DebugMesh
{
protected:

	// 位置
	DirectX::SimpleMath::Vector3 m_position;

	// 回転
	DirectX::SimpleMath::Quaternion m_rotation;

private:

	// コリジョン用三角形データ
	std::vector<MyCollisionObject::Triangle> m_triangles;

	// インデックス数
	int m_indexCnt;

	struct ConstantBuffer
	{
		DirectX::XMMATRIX worldViewProjection;
	};

	// 深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;

	// ラスタライザステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// コリジョン用三角形データの追加関数
	//void AddTriangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c);

	// 描画
	void Draw(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

public:
	// コンストラクタ
	DebugMesh(ID3D11Device* device, wchar_t* fname);

	// 位置を設定する関数
	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	// 回転を設定する関数
	void SetRotation(DirectX::SimpleMath::Quaternion rotation) { m_rotation = rotation; }

	// デバッグ用コリジョン表示関数
	void DrawCollision(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// メッシュの三角形ポリゴンの数を取得する関数
	int GetTriangleCnt();

	// 指定インデックスのコリジョン用三角形データを取得する関数
	//const Collision::Triangle& GetTriangle(int id);

	// 線分との交差判定関数
	//bool HitCheck_Segment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, int* id, DirectX::SimpleMath::Vector3* hit_pos);
};