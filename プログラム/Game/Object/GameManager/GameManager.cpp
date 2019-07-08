#include "../../../pch.h"
#include "GameManager.h"
#include "../../Component/Object/GameJudge.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameManager::~GameManager()
{
}

/// <summary>
/// 生成
/// </summary>
void GameManager::Instance(Player* player, Enemy* enemy, PlayCamera* camera, TimerCounter* timer)
{
	// ゲーム判定のコンポーネントを作成
	GameJudge* gameJudge = new GameJudge();
	gameJudge->SetPlayer(player);
	gameJudge->SetEnemy(enemy);
	gameJudge->SetCamera(camera);
	gameJudge->SetTimer(timer);
	AddComponent(gameJudge);
}
