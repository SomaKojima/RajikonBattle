#include "../../../pch.h"
#include "RenderThreeDimension.h"
#include "../../SubGame.h"
#include "../../../DebugString.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

RenderThreeDimention::RenderThreeDimention(DirectX::Model* model, Type type)
	:
	m_model(model),
	m_type(type),
	m_emissionColor(Vector3::One)
{
}

RenderThreeDimention::~RenderThreeDimention()
{
}

void RenderThreeDimention::Render()
{
	// モデルがない場合
	if (!m_model) return;
	// スカイドームを描画する際の処理
	if (m_type == Type::Sky)
	{
		m_model->UpdateEffects([&](IEffect* effect) {
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights) {
				// ライトの影響をなくす 
				lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// エミッション色を白に設定する 
				basicEffect->SetEmissiveColor(Vector3(1, 1, 1));
			}
		});
	}
	// ゲームを取得
	Game* game = SubGame::GetInstace().GetGame();

	// 描画
	if (game)
	{
		m_model->Draw(game->GetContext(), *game->GetStates(), m_gameObject->GetTransform().WorldMatrix(), game->GetView(), game->GetProjection());
	}
}

void RenderThreeDimention::Finalize()
{
}
