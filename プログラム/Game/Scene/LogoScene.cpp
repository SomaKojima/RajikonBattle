#include "../../pch.h"
#include "LogoScene.h"
#include "../Object/Logo/Logo.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
LogoScene::LogoScene()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LogoScene::~LogoScene()
{
}

/// <summary>
/// ����
/// </summary>
void LogoScene::Instance()
{
	// ���S�̍쐬
	GameObject* logo = new Logo();
	logo->Instance();
	m_gameObjectList.Add(logo);
}
