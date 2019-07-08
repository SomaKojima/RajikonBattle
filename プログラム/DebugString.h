#pragma once

// インクルード
#include "Game\Utility\Singleton.h"
#include <list>
#include "StepTimer.h"

// 文字のデバッグクラス
class DebugString : public Singleton<DebugString>
{
public:
	enum STATE
	{
		PLAY,
		STOP,

		STATE_MAX
	};
	const int FLASH_INTERVAL = 15;
public:
	const unsigned int MAX = 10;
public:
	DebugString();
	~DebugString();

public:
	void Initialize(DirectX::SpriteBatch* sprites, DirectX::SpriteFont* font);
	void Update(DX::StepTimer const& timer);
	void Render();

	void Reset();

	void DebugText(std::string str);
	std::string ToS(int num);
	std::string ToS(float num);
	std::string ToS(DirectX::SimpleMath::Vector3 vec);
	std::string ToS(DirectX::SimpleMath::Vector2 vec);

	void SetState(STATE state) { 
		switch (state)
		{
		case DebugString::PLAY:
			m_isStop = false;
			break;
		case DebugString::STOP:
			m_isStop = true;
			break;
		}
		m_state = state; 
	}

private:
	uint32_t m_fps;
	bool m_isStop;
	// スプライトバッチ
	DirectX::SpriteBatch* m_sprites;
	// スプライトフォント
	DirectX::SpriteFont* m_font;

	std::list<std::string> m_strings;

	int m_flashTime;
	std::string m_stateStr[STATE::STATE_MAX];
	STATE m_state;
};