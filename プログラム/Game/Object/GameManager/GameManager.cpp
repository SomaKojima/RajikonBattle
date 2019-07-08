#include "../../../pch.h"
#include "GameManager.h"
#include "../../Component/Object/GameJudge.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameManager::GameManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameManager::~GameManager()
{
}

/// <summary>
/// ����
/// </summary>
void GameManager::Instance(Player* player, Enemy* enemy, PlayCamera* camera, TimerCounter* timer)
{
	// �Q�[������̃R���|�[�l���g���쐬
	GameJudge* gameJudge = new GameJudge();
	gameJudge->SetPlayer(player);
	gameJudge->SetEnemy(enemy);
	gameJudge->SetCamera(camera);
	gameJudge->SetTimer(timer);
	AddComponent(gameJudge);
}
