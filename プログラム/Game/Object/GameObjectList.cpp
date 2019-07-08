#include "../../pch.h"
#include "GameObject.h"
#include "GameObjectList.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObjectList::GameObjectList()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObjectList::~GameObjectList()
{
}

/// <summary>
/// ����������
/// </summary>
void GameObjectList::Initialize()
{
	// �ǉ��̃��X�g���X�V
	while (m_addList.GetTop())
	{
		m_addList.GetTop()->GetElement().Initialize();
		m_list.Add(m_addList.GetTop());
	}
	BidirectionalList<GameObject>* obj = nullptr;
	obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().Initialize();
		obj = obj->GetNext();
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void GameObjectList::Update(float elapsedTime)
{
	// �ǉ��̃��X�g���X�V
	while (m_addList.GetTop())
	{
		m_addList.GetTop()->GetElement().Initialize();
		m_list.Add(m_addList.GetTop());
	}

	// ���X�g���}�g���N�X���X�V����
	BidirectionalList<GameObject>* obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().UpdateTransform(elapsedTime);
		obj = obj->GetNext();
	}

	// ���X�g���X�V����
	obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().Update(elapsedTime);
		// �폜����ꍇ
		if (obj->GetElement().IsDelete())
		{
			BidirectionalList<GameObject>* buf = obj->GetNext();
			m_deleteList.Add(obj);
			obj = buf;
			continue;
		}
		obj = obj->GetNext();
	}

	// �폜���X�g�̍X�V����
	BidirectionalList<GameObject>* deleteObj = m_deleteList.GetTop();
	while (deleteObj)
	{
		deleteObj->GetElement().Finalize();
		deleteObj = deleteObj->GetNext();
	}
	m_deleteList.Clear();

}

/// <summary>
/// �`�揈��
/// </summary>
void GameObjectList::Render()
{
	BidirectionalList<GameObject>* obj = nullptr;
	obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().Render();
		obj = obj->GetNext();
	}
}

/// <summary>
/// �I������
/// </summary>
void GameObjectList::Finalize()
{
	// ���X�g�̏���
	BidirectionalList<GameObject>* obj = nullptr;
	obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().Finalize();
		obj = obj->GetNext();
	}
	m_list.Clear();

	// �폜���X�g�̏���
	BidirectionalList<GameObject>* deleteObj = m_deleteList.GetTop();
	while (deleteObj)
	{
		deleteObj->GetElement().Finalize();
		deleteObj = deleteObj->GetNext();
	}
	m_deleteList.Clear();

	// �ǉ����X�g�̏���
	BidirectionalList<GameObject>* addObj = m_addList.GetTop();
	while (addObj)
	{
		addObj->GetElement().Finalize();
		addObj = addObj->GetNext();
	}
	m_addList.Clear();
}

/// <summary>
/// �ǉ����X�g�ɃQ�[���I�u�W�F�N�g��ǉ�����
/// </summary>
/// <param name="gameObject"></param>
void GameObjectList::Add(GameObject * gameObject)
{
	gameObject->Remove();
	m_addList.Add(gameObject);
}

/// <summary>
/// �폜���X�g�ɃQ�[���I�u�W�F�N�g��ǉ�����
/// </summary>
/// <param name="gameObject"></param>
void GameObjectList::Delete(GameObject * gameObject)
{
	gameObject->Remove();
	m_deleteList.Add(gameObject);
}

/// <summary>
/// �I�u�W�F�N�g������
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
GameObject * GameObjectList::Find(const char * name)
{
	// ���X�g�̏���
	BidirectionalList<GameObject>* obj = nullptr;
	obj = m_list.GetTop();
	while (obj)
	{
		if (obj->GetElement().GetName() == name)
		{
			return &obj->GetElement();
		}
		obj = obj->GetNext();
	}
	return nullptr;
}
