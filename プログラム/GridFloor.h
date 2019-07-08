//--------------------------------------------------------------------------------------
// File: GridFloor.h
//
// グリッドの床を描画するクラス
//
// Date: 2018.4.14
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

//--------------------------------------------------------------------------------------
//　グリッドの床描画クラス
//--------------------------------------------------------------------------------------
class GridFloor
{
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// コモンステートへのポインタ
	DirectX::CommonStates* m_states;

	// 床の一辺のサイズ
	float m_size;

	// 分割数
	int m_divs;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="device">DirectXのデバイス</param>
	/// <param name="context">DirectXのコンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="size">床の一辺のサイズ</param>
	/// <param name="divs">一辺の分割数</param>
	GridFloor(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::CommonStates* states, float size, int divs);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GridFloor();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="context">DirectXのコンテキスト</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <param name="color">描画色</param>
	void Render(ID3D11DeviceContext* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);
};



