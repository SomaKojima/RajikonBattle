#pragma once

#include <list>
#include "Transform.h"
#include "../Utility/BidirectionalList.h"
#include "../Data/Data.h"

class Component;
class GameObjectList;

namespace MyCollisionObject
{
	class CollisionObject;
}


/// <summary>
/// �Q�[���I�u�W�F�N�g�̃N���X
/// </summary>
class GameObject : public BidirectionalList<GameObject>
{
public:
	// �R���X�g���N�^
	GameObject();
	// �f�X�g���N�^
	virtual ~GameObject();

public:
	// �����֐�
	virtual void Instance() {};

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �}�g���N�X�̍X�V
	void UpdateTransform(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
	// �Փˏ���
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& col, DirectX::SimpleMath::Vector3 &hitPos);
	// ����
	void Delete();

public:
	// �q�������X�g�ɒǉ�����
	void AddChild(GameObject* gameObject);

	// �R���|�[�l���g�̃N���X�ɒǉ�����
	void AddComponent(Component* component);
	/// <summary>
	/// �R���|�[�l���g���擾����֐�
	/// </summary>
	std::list<Component*>& GetComponentList() { return m_componentList; }
	template<class T>
	inline T* GetComponent();
	template<class T>
	inline T* GetComponent(Component* component);
	template<class T>
	inline std::list<T*> GetComponentList();

	// �ό`�̎擾
	Transform& GetTransform() { return m_transform; }
	// �^�O�̐ݒ�
	void SetTag(Tag tag) { m_tag = tag; }
	// �^�O�̎擾
	Tag& GetTag() { return m_tag; }
	// ���O�̐ݒ�
	void SetName(char* name) { m_name = name; }
	// ���O�̎擾
	char* GetName() { return m_name; }
	// �폜�t���O���擾����
	bool IsDelete() { return m_delete; }

	GameObjectList& GetChildList() { return *m_childGameObjectList; }
	void SetParent(GameObject* parent) { m_parent = parent; }
	GameObject* GetParent() { return m_parent; }

private:
	// �q�̃Q�[���I�u�W�F�N�g�̃��X�g
	GameObjectList* m_childGameObjectList;
	// �e
	GameObject* m_parent;
	// �ό`
	Transform m_transform;
	// �R���|�[�l���g�̃��X�g
	std::list<Component*> m_componentList;
	// �^�O
	Tag m_tag;
	// ���O
	char* m_name;
	// �폜�t���O
	bool m_delete;
};

/// <summary>
/// �R���|�[�l���g�̃��X�g�����̃R���|�[�l���g���擾����
/// </summary>
template<class T>
inline T * GameObject::GetComponent()
{
	T* sub = nullptr;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// �����̃|�C���^����R���|�[�l���g���擾����
/// </summary>
template<class T>
inline T * GameObject::GetComponent(Component * component)
{
	T* sub = nullptr;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub == component)
		{
			return sub;
		}
	}
	return nullptr;
}

/// <summary>
/// �R���|�[�l���g�̃��X�g���畡���̃R���|�[�l���g�����X�g�Ŏ擾����
/// </summary>
template<class T>
inline std::list<T*> GameObject::GetComponentList()
{
	T* sub = nullptr;
	std::list<T*> list;
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			list.push_back(sub);
		}
	}
	return list;
}
