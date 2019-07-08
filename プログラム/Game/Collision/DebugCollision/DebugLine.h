//--------------------------------------------------------------------------------------
// File: DebugLine.h
//
// デバッグラインを描画するクラス
//
// Date: 2018.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

class DebugLine
{
	struct Line
	{
		DirectX::SimpleMath::Vector3 p;	// スタート位置
		DirectX::SimpleMath::Vector3 d;	// 方向ベクトル
		DirectX::XMFLOAT4 color;		// 色
	};

	// 描画するライン情報
	std::vector<Line> m_lines;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// コモンステートへのポインタ
	DirectX::CommonStates* m_states;

public:
	//コンストラクタ
	DebugLine(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::CommonStates* states);

	// 描画
	void Render(ID3D11DeviceContext* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// ラインの追加
	/// </summary>
	/// <param name="p">開始位置</param>
	/// <param name="d">ベクトル</param>
	/// <param name="color">色</param>
	void AddLine(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 d, DirectX::GXMVECTOR color = DirectX::Colors::White);

	/// <summary>
	/// ラインの追加
	/// </summary>
	/// <param name="a">開始位置</param>
	/// <param name="b">終了位置</param>
	/// <param name="color">色</param>
	void AddLine_Point2Point(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::GXMVECTOR color = DirectX::Colors::White);
};

