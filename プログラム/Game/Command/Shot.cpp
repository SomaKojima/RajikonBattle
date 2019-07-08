#include "../../pch.h"
#include "Shot.h"

#include "../Scene/SceneManager.h"
#include "../Object/Bullet/PlayerBullet.h"
#include "../../DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float Command::Shot::SHOT_SPEED = 2.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Command::Shot::Shot()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Command::Shot::~Shot()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="obj"></param>
void Command::Shot::Excute(GameObject & obj)
{
	float speed = -SHOT_SPEED;
	// �e�̍쐬
	GameObject* bullet = new PlayerBullet();
	bullet->Instance();
	bullet->GetTransform().WorldPos(obj.GetTransform().WorldPos());
	bullet->GetTransform().WorldVel(Vector3::Transform(Vector3(0, 0, speed), obj.GetTransform().WorldDir()));

	//�@�I�u�W�F�N�g��ǉ�
	SceneManager& sceneManager = SceneManager::GetInstace();
	sceneManager.GetGameObjectList().Add(bullet);
}
