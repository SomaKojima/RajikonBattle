#include "../../pch.h"
#include "GameObject.h"
#include "../Component/Component.h"
#include "../Component/Collision/CollisionComponent.h"
#include "../Collision/CCell.h"
#include "../Object/GameObjectList.h"
#include "../Collision/CollisionObject.h"


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObject::GameObject() 
	: 
	BidirectionalList<GameObject>(this),
	m_tag(Tag::Tag_Default),
	m_name(""),
	m_delete(false),
	m_childGameObjectList(new GameObjectList()),
	m_parent(nullptr)
{
	// �ό`�̃Q�[���I�u�W�F�N�g��ݒ肷��
	m_transform.SetGameObject(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// ������
/// </summary>
void GameObject::Initialize()
{
	// �ό`�̍X�V
	m_transform.Update(0);

	// �R���|�[�l���g�̏�����
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Initialize();
	}
	m_childGameObjectList->Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::Update(float elapsedTime)
{
	// �R���|�[�l���g�̍X�V
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Update(elapsedTime);
	}
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->LateUpdate(elapsedTime);
	}

	m_childGameObjectList->Update(elapsedTime);
}

/// <summary>
/// �}�g���N�X�̍X�V
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::UpdateTransform(float elapsedTime)
{
	// �ό`�̍X�V
	m_transform.Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
void GameObject::Render()
{
	// �R���|�[�l���g�̕`��
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Render();
	}
	m_childGameObjectList->Render();
}

/// <summary>
/// �I��
/// </summary>
void GameObject::Finalize()
{
	if (GetName() == "Bullet")
	{
		int a = 0;
	}
	// �R���|�[�l���g�̏I��
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Finalize();
		delete (*ite);
	}
	m_componentList.clear();

	m_childGameObjectList->Finalize();
	delete m_childGameObjectList;
}

/// <summary>
/// �Փ�
/// </summary>
/// <param name="obj"></param>
/// <param name="data"></param>
void GameObject::OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& col, DirectX::SimpleMath::Vector3 &hitPos)
{
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->OnCollision(obj, col, hitPos);
	}
}

/// <summary>
/// ����
/// </summary>
void GameObject::Delete()
{
	m_delete = true;
}

/// <summary>
/// �q�����X�g�ɒǉ�
/// </summary>
/// <param name="gameObject"></param>
void GameObject::AddChild(GameObject * gameObject)
{
	gameObject->SetParent(this);
	m_childGameObjectList->Add(gameObject);
}

/// <summary>
/// �R���|�[�l���g�����X�g�ɒǉ�����
/// </summary>
/// <param name="component"></param>
void GameObject::AddComponent(Component * component)
{
	component->SetGameObjec(this);
	m_componentList.push_back(component);
}
