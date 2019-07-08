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
	// ���f�����Ȃ��ꍇ
	if (!m_model) return;
	// �X�J�C�h�[����`�悷��ۂ̏���
	if (m_type == Type::Sky)
	{
		m_model->UpdateEffects([&](IEffect* effect) {
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights) {
				// ���C�g�̉e�����Ȃ��� 
				lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �G�~�b�V�����F�𔒂ɐݒ肷�� 
				basicEffect->SetEmissiveColor(Vector3(1, 1, 1));
			}
		});
	}
	// �Q�[�����擾
	Game* game = SubGame::GetInstace().GetGame();

	// �`��
	if (game)
	{
		m_model->Draw(game->GetContext(), *game->GetStates(), m_gameObject->GetTransform().WorldMatrix(), game->GetView(), game->GetProjection());
	}
}

void RenderThreeDimention::Finalize()
{
}
