//--------------------------------------------------------------------------------------
// File: GridFloor.cpp
//
// グリッドの床を描画するクラス
//
// Date: 2018.4.14
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "GridFloor.h"
#include <algorithm>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
GridFloor::GridFloor(ID3D11Device* device, ID3D11DeviceContext* context, CommonStates* states, float size, int divs) : m_size(size), m_divs(divs), m_states(states)
{
	// エフェクトの生成
	m_basicEffect = std::make_unique<BasicEffect>(device);
	// 頂点カラー(有効)
	m_basicEffect->SetVertexColorEnabled(true);
	// プリミティブオブジェクト生成
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	// インプットレイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_pInputLayout.GetAddressOf());
}

//--------------------------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------------------------
GridFloor::~GridFloor()
{
	// エフェクトを解放する
	m_basicEffect.reset();
	// 入力レイアウトを解放する
	m_pInputLayout.Reset();
}

//--------------------------------------------------------------------------------------
// 描画
//--------------------------------------------------------------------------------------
void GridFloor::Render(ID3D11DeviceContext* context, Matrix view, Matrix proj, GXMVECTOR color)
{
	Matrix world;

	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	m_basicEffect->Apply(context);
	context->IASetInputLayout(m_pInputLayout.Get());

	m_primitiveBatch->Begin();

	const XMVECTORF32 xAxis = { m_size, 0.f, 0.f };
	const XMVECTORF32 yAxis = { 0.f, 0.f, m_size };

	size_t divs = std::max<size_t>(1, m_divs);
	FXMVECTOR origin = g_XMZero;
	for (size_t i = 0; i <= divs; ++i)
	{
		float fPercent = float(i) / float(divs);
		fPercent = (fPercent * 1.0f) - 0.5f;
		XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
		vScale = XMVectorAdd(vScale, origin);

		VertexPositionColor v1(XMVectorSubtract(vScale, yAxis * 0.5f), color);
		VertexPositionColor v2(XMVectorAdd(vScale, yAxis * 0.5f), color);
		m_primitiveBatch->DrawLine(v1, v2);
	}

	for (size_t i = 0; i <= divs; i++)
	{
		FLOAT fPercent = float(i) / float(divs);
		fPercent = (fPercent * 1.0f) - 0.5f;
		XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
		vScale = XMVectorAdd(vScale, origin);

		VertexPositionColor v1(XMVectorSubtract(vScale, xAxis * 0.5f), color);
		VertexPositionColor v2(XMVectorAdd(vScale, xAxis * 0.5f), color);
		m_primitiveBatch->DrawLine(v1, v2);
	}

	m_primitiveBatch->End();
}

