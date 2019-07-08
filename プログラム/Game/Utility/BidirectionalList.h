#pragma once

/// <summary>
/// �g�����̗�
/// </summary>

/// <summary>
/// �o�^�����I�u�W�F�N�g�N���X�i���X�g�̗v�f�ƂȂ�N���X�j
/// </summary>
/*

class EntityOfTree : public BidirectionalList<Entity>
{
public:
	EntityOfTree(Entity* obj) : BidirectionalList(obj) {}
	~EntityOfTree() {}

};

*/

/// <summary>
/// �o�^�����̃N���X
/// </summary>
/*

class EntityList : public BidirectionalList<Entity>::RegisterTo
{
public:
	EntityList() {}
	~EntityList() {}
};

*/

/// <summary>
/// �o�^�����I�u�W�F�N�g�N���X�i���X�g�̗v�f�ƂȂ�N���X�j
/// </summary>
template<class T> class BidirectionalList
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="obj"></param>
	BidirectionalList(T* obj) : m_pPre(nullptr), m_pNext(nullptr), m_pRegisterTo(nullptr), m_pObj(obj) { }

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BidirectionalList() { m_pPre = nullptr; m_pNext = nullptr; m_pRegisterTo = nullptr; m_pObj = nullptr; }

public:
	/// <summary>
	/// �o�^��̃N���X
	/// </summary>
	class RegisterTo
	{
	public:
		RegisterTo() : m_pTop(nullptr) {}
		virtual ~RegisterTo() {}

		bool Add(BidirectionalList<T>* obj);

		void SetTop(BidirectionalList<T>* top) { m_pTop = top; }
		BidirectionalList<T>* GetTop() { return m_pTop; }

		void Clear();

	protected:
		BidirectionalList<T>* m_pTop;
	};

public:
	// ���X�g��̃N���X���痣���(���X�g����폜)
	bool Remove();

	// getter
	BidirectionalList<T>* GetPre() { return m_pPre; }
	BidirectionalList<T>* GetNext() { return m_pNext; }
	RegisterTo* GetRegisterTo() { return m_pRegisterTo; }
	T& GetElement() { return *m_pObj; }

private:
	// setter
	void SetPre(BidirectionalList<T>* bl) { m_pPre = bl; }
	void SetNext(BidirectionalList<T>* bl) { m_pNext = bl; }
	void SetRegisterTo(RegisterTo* registerTo) { m_pRegisterTo = registerTo; }

private:
	BidirectionalList<T>* m_pPre;
	BidirectionalList<T>* m_pNext;

	RegisterTo* m_pRegisterTo;

	// �o�^����Ă���I�u�W�F�N�g�̍폜
	T* m_pObj;
};

template<class T>
inline bool BidirectionalList<T>::Remove()
{
	// �o�^����Ă��Ȃ��ꍇ
	if (!m_pRegisterTo)
	{
		return false;
	}

	// �O�̃|�C���^�̏���
	if (!m_pPre)
	{
		m_pRegisterTo->SetTop(m_pNext);
	}
	else
	{
		m_pPre->SetNext(m_pNext);
	}

	// ���̃|�C���^�̏���
	if (m_pNext)
	{
		m_pNext->SetPre(m_pPre);
	}

	m_pPre = nullptr;
	m_pNext = nullptr;

	m_pRegisterTo = nullptr;
	return true;
}

template<class T>
inline bool BidirectionalList<T>::RegisterTo::Add(BidirectionalList<T>* obj)
{
	// ��d�o�^�h�~
	if (obj->GetRegisterTo() == this)
	{
		return false;
	}

	obj->Remove();
	if (!m_pTop)
	{
		obj->SetRegisterTo(this);
		obj->SetPre(nullptr);
		obj->SetNext(nullptr);
		m_pTop = obj;
		return true;
	}

	obj->SetRegisterTo(this);
	obj->SetPre(nullptr);
	obj->SetNext(m_pTop);

	// ���ݐ擪��OFT��ς���
	m_pTop->SetPre(obj);
	m_pTop = obj;

	return true;
}

template<class T>
inline void BidirectionalList<T>::RegisterTo::Clear()
{
	T* obj = nullptr;
	while (m_pTop)
	{
		// ���X�g�̐擪�ɓ����Ă���v�f���擾
		obj = &m_pTop->GetElement();
		// ���X�g���痣���
		m_pTop->Remove();
		// ����Ă������
		delete obj;
	}
}
