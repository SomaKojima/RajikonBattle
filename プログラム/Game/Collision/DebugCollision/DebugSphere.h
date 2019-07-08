//--------------------------------------------------------------------------------------
// File: DebugSphere.h
//
// デバッグスフィアを描画するクラス
//
// Date: 2018.6.4
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

class DebugSphere
{
	struct ConstantBuffer
	{
		DirectX::XMMATRIX worldViewProjection;
	};

	// 中心
	DirectX::SimpleMath::Vector3 m_center;

	// 半径
	float m_radius;

	// 平行移動行列
	DirectX::SimpleMath::Matrix m_trans;

	// スケール行列
	DirectX::SimpleMath::Matrix m_scale;

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

public:
	// コンストラクタ
	DebugSphere(ID3D11Device* device, DirectX::SimpleMath::Vector3 center, float radius);

	// デバッグスフィアの描画関数
	void Draw(ID3D11DeviceContext* context, DirectX::CommonStates& states, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	// デバッグスフィアのセンターの設定関数
	void SetCenter(DirectX::SimpleMath::Vector3 center);

	// デバッグスフィアの半径の設定関数
	void SetRadius(float radius);

	// デバッグスフィアのセンターの取得関数
	DirectX::SimpleMath::Vector3 GetCenter();

	// デバッグスフィアの半径の取得関数
	float GetRadius();

};
