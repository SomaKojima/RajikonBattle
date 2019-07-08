#pragma once
#include "../GameObject.h"

class Player;
class Enemy;
class PlayCamera;
class GameJudge;
class TimerCounter;

class GameManager : public GameObject
{
public:
	// �R���X�g���N�^
	GameManager();
	// �f�X�g���N�^
	~GameManager();

public:
	// �����֐�
	void Instance(Player* player, Enemy* enemy, PlayCamera* camera, TimerCounter* timer) ;
};
