#pragma once
#include "../Utility/BidirectionalList.h"

class GameObject;

class GOList : public BidirectionalList<GameObject>::RegisterTo
{
};

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃��X�g�N���X
/// </summary>
class GameObjectList
{
public:
	// �R���X�g���N�^
	GameObjectList();
	// �f�X�g���N�^
	~GameObjectList();

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	void Add(GameObject* gameObject);
	void Delete(GameObject* gameObject);
	GameObject* Find(const char* name);

	GOList& GetList() { return m_list; }

private:
	GOList m_list;
	GOList m_addList;
	GOList m_deleteList;
};