#include "../../pch.h"
#include "TimeCounter.h"
#include "../../SubGame.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const int TimerCounter::NUM_WIDTH = 32;
const int TimerCounter::NUM_HEIGHT = 64;
const float TimerCounter::TIMER = 101.0f;
const float TimerCounter::START_TIMER = 4.0f;

/// <summary>
///	コンストラクタ
/// </summary>
TimerCounter::TimerCounter(ID3D11ShaderResourceView* texture, RECT rect, float time)
	:
	m_texture(texture),
	m_rect(rect),
	m_time(time),
	m_timeMax(time),
	m_startTime(START_TIMER),
	m_isStop(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
TimerCounter::~TimerCounter()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void TimerCounter::Update(float elapsedTime)
{
	if (m_isStop) return;

	m_startTime -= elapsedTime;
	if (m_startTime <= 0)
	{
		m_startTime = 0;

		m_time -= elapsedTime;
		if (m_time <= 0)
		{
			m_time = 0;
		}
	}
}

void TimerCounter::Render()
{
	if (!m_texture) return;

	int time = (int)m_time;
	if (m_startTime > 0) time = m_startTime;

	Vector2 pos = m_gameObject->GetTransform().WorldPos() + Vector2(GetDigit(time) * 0.5f * NUM_WIDTH, 0.0f);

	int digit = 1;
	int buf = (time % (10 * digit)) / digit;
	while (((time - (time % (10 * digit))) > 0 )|| buf)
	{
		// 数字の描画
		DrawNum(buf, pos);

		digit *= 10;
		buf = (time % (10 * digit)) / digit;
		pos.x -= NUM_WIDTH;
	}
}

/// <summary>
/// 数字の描画
/// </summary>
/// <param name="num"></param>
void TimerCounter::DrawNum(int num, DirectX::SimpleMath::Vector2 pos)
{
	if (!m_texture) return;

	RECT rect = m_rect;
	int width = m_rect.right / 10;
	int height = m_rect.bottom;
	rect.left = num * width;
	rect.right = rect.left + width;

	SubGame& subGame = SubGame::GetInstace();
	subGame.GetGame()->GetSpriteBatch()->Draw(m_texture, Vector2(pos.x, pos.y), &rect, Colors::White,
		0.0f, Vector2(width, 0.0f), 1.0f, DirectX::SpriteEffects_None);
}

/// <summary>
/// 桁数を取得する
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
unsigned TimerCounter::GetDigit(unsigned num) {
	unsigned digit = 0;
	while (num != 0) {
		num /= 10;
		digit++;
	}
	return digit;
}