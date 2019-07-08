//--------------------------------------------------------------------------------------
// File: DebugLine.cpp
//
// デバッグラインを描画するクラス
//
// Date: 2018.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "../../../pch.h"
#include "DebugLine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

DebugLine::DebugLine(ID3D11Device * device, ID3D11DeviceContext * context, DirectX::CommonStates * states)
: m_states(states)
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

void DebugLine::Render(ID3D11DeviceContext* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	VertexPositionColor a, b;

	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	Matrix world;
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	m_basicEffect->Apply(context);
	context->IASetInputLayout(m_pInputLayout.Get());

	m_primitiveBatch->Begin();

	for (auto line : m_lines)
	{
		a.position = line.p;
		b.position = line.p + line.d;
		a.color = b.color = line.color;
		m_primitiveBatch->DrawLine(a, b);
	}

	m_primitiveBatch->End();

	m_lines.clear();
}

void DebugLine::AddLine(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 d, DirectX::GXMVECTOR color)
{
	Line line;
	line.p = p;
	line.d = d;
	XMStoreFloat4(&line.color, color);
	m_lines.push_back(line);
}

void DebugLine::AddLine_Point2Point(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::GXMVECTOR color)
{
	AddLine(a, b - a, color);
}
