#pragma once

#include "../Component.h"

/// <summary>
/// 2D�X�v���C�g�`��̃R���|�[�l���g
/// </summary>
class TwoDimentionSprite : public Component
{
public:
	// �R���X�g���N�^
	TwoDimentionSprite(ID3D11ShaderResourceView* texture, RECT rect,
		float depth = 0.0f, DirectX::XMVECTOR color = DirectX::Colors::White);
	// �f�X�g���N�^
	~TwoDimentionSprite();

public:
	// �`��
	void Render()override;
	// �I��
	void Finalize()override;

	void SetRECT(RECT rect) { m_rect = rect; }
	void SetDepth(float depth) { m_depth = depth; }

	void SetTexture(ID3D11ShaderResourceView* texture) { m_texture = texture; }

	RECT GetRECT() { return m_rect; }
	float GetDepth() { return m_depth; }
	RECT GetScreenRECT();

	bool GetVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	DirectX::XMVECTOR GetColor() { return DirectX::XMLoadFloat4(&m_color); }
	void SetColor(DirectX::XMVECTOR color) { XMStoreFloat4(&m_color, color); }

	DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }
	void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; }
	void SetScale(float scale) { m_scale = DirectX::SimpleMath::Vector2(scale, scale); }


	DirectX::SimpleMath::Vector2 GetOrigin() { return m_origin; }
	void SetOrigin(DirectX::SimpleMath::Vector2 origin) { m_origin = origin; }

private:
	bool m_visible;
	ID3D11ShaderResourceView* m_texture;			// �e�N�X�`���n���h��
	RECT m_rect;
	float m_depth;				// �[�x
	DirectX::XMFLOAT4 m_color;
	DirectX::SimpleMath::Vector2 m_scale;
	DirectX::SimpleMath::Vector2 m_origin;
};