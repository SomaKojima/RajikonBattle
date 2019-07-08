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
	// コンストラクタ
	GameManager();
	// デストラクタ
	~GameManager();

public:
	// 生成関数
	void Instance(Player* player, Enemy* enemy, PlayCamera* camera, TimerCounter* timer) ;
};
