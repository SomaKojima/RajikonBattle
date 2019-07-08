#pragma once

#include "../Component.h"
#include "../../../ADX2/ADX2Le.h"

class PlayCamera;
class Player;
class Enemy;
class StatusHP;
class PlayerController;
class EnemyController;
class TimerCounter;

/// <summary>
/// ゲーム判定のコンポーネント
/// </summary>
class GameJudge : public Component
{
public:
	static const float RESUTL_TO_CHANGE_TIME;
public:
	// コンストラクタ
	GameJudge();
	// デストラクタ
	~GameJudge();

public:
	// 更新処理
	void Update(float elapsedTime) override;
	// プレイヤーが勝った時の処理
	void PlayerWin();
	// 敵が勝った時の処理
	void EnemyWin();
	// 時間切れ
	void TimeUp();
	// 開始3秒
	void StartThreeTime();
	// 開始
	void Start();
	// リザルトに移行するとき
	void ResultStart();

	// プレイヤーの情報を設定する
	void SetPlayer(Player* player);
	// プレイヤーの情報を初期化する
	void InitPlayerInfo();
	// 敵の情報を設定する
	void SetEnemy(Enemy* enemy);
	// 敵の情報を初期化する
	void InitEnemyInfo();
	// カメラの情報を設定する
	void SetCamera(PlayCamera* camera);
	// タイマーの情報を設定する
	void SetTimer(TimerCounter* timer);

private:
	bool m_isStart;
	Player* m_player;
	StatusHP* m_playerHP;
	PlayerController* m_playerController;
	Enemy* m_enemy;
	StatusHP* m_enemyHP;
	EnemyController* m_enemyController;
	PlayCamera* m_camera;
	TimerCounter* m_timer;
	bool m_isResult;
	float m_resultTime;
	MyLibrary::ADX2Le* m_a;
	CriAtomExPlaybackId m_id;
};