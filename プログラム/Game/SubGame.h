#pragma once

#include "Utility/Singleton.h"

class Game;

class SubGame : public Singleton<SubGame>
{
public:
	//�@�R���X�g���N�^
	SubGame();
	~SubGame();
public:
	// ����������
	void Initialize(Game* game);
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Renderer();
	// �I������
	void Finalize();

	void SetGame(Game* game) { m_game = game; }
	Game* GetGame() { return m_game; }
	
	void SetWindow(HWND window) { m_window = window; }
	HWND GetWindow() { return m_window; }


	bool IsStop() { return m_isStop; }
	void Stop() { m_isStop = true; }
	void Start() { m_isStop = false; }

private:
	Game* m_game;
	HWND m_window;
	bool m_isStop;
};