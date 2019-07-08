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
/// �Q�[������̃R���|�[�l���g
/// </summary>
class GameJudge : public Component
{
public:
	static const float RESUTL_TO_CHANGE_TIME;
public:
	// �R���X�g���N�^
	GameJudge();
	// �f�X�g���N�^
	~GameJudge();

public:
	// �X�V����
	void Update(float elapsedTime) override;
	// �v���C���[�����������̏���
	void PlayerWin();
	// �G�����������̏���
	void EnemyWin();
	// ���Ԑ؂�
	void TimeUp();
	// �J�n3�b
	void StartThreeTime();
	// �J�n
	void Start();
	// ���U���g�Ɉڍs����Ƃ�
	void ResultStart();

	// �v���C���[�̏���ݒ肷��
	void SetPlayer(Player* player);
	// �v���C���[�̏�������������
	void InitPlayerInfo();
	// �G�̏���ݒ肷��
	void SetEnemy(Enemy* enemy);
	// �G�̏�������������
	void InitEnemyInfo();
	// �J�����̏���ݒ肷��
	void SetCamera(PlayCamera* camera);
	// �^�C�}�[�̏���ݒ肷��
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