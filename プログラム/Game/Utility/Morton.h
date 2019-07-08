#pragma once
#include "BidirectionalList.h"
#include <list>

/// <summary>
/// ��ԏ��
/// </summary>
struct CellRoomInfo
{
	CellRoomInfo() :left(0), bottom(0), back(0), width(0), height(0), depth(0) {}

	CellRoomInfo(float _left, float _bottom, float _back, float _width, float _height, float _depth):
		left(_left), bottom(_bottom), back(_back), width(_width), height(_height), depth(_depth) {}

	float left;
	float bottom;
	float back;
	
	float width;
	float height;
	float depth;
};

/// <summary>
/// �ڐG��ԏ��
/// </summary>
template<class T> class CellInfo
{
public:
	// �R���X�g���N�^
	CellInfo() : obj(nullptr){}

	T* obj;
	std::list<T*> colList;
};

template<class T> class Morton
{
public:
	static const int CLINER8TREEMANAGER_MAXLEVEL = 4;

public:
	Morton();
	virtual ~Morton();

	// ������
	bool Init(unsigned int Level, CellRoomInfo room);

	// �r�b�g�����炷
	DWORD BitSeparateFor3D(BYTE n);
	// xyz���烂�[�g���ԍ����Z�o
	DWORD Get3DMortonOrder(BYTE x, BYTE y, BYTE z);
	// vector3���烂�[�g���ԍ����Z�o
	DWORD GetPosToMortonOrder(const DirectX::SimpleMath::Vector3& pos);
	// �Q���_�iMIN�AMAX�j���烂�[�g���ԍ����Z�o
	DWORD Get2PointMortonOrder(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max);

	// ��Ԃ̐���
	bool CreateNewCell(DWORD Elem);
	// �o�^
	bool Register(BidirectionalList<T>& collision, const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max);

	// ��Ԃ𔻒肵�ĐڐG���Ă����Ԃ̃��X�g���擾����
	DWORD GetList(std::vector<T*>& colVect);

	bool CheckCell(int elem, std::list<BidirectionalList<T>*>& cStack, std::vector<T*>& cellInfoList);

	typename BidirectionalList<T>::RegisterTo** GetCCell() { return ppCellAry; }

protected:
	CellRoomInfo m_room;
	DirectX::SimpleMath::Vector3 m_fUnit;
	int m_level;
	int m_iPow[CLINER8TREEMANAGER_MAXLEVEL];
	unsigned int m_dwCellNum;

	typename BidirectionalList<T>::RegisterTo** ppCellAry;
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
template<class T>
Morton<T>::Morton()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
template<class T>
Morton<T>::~Morton()
{
	for (int i = 0; i < (int)m_dwCellNum; i++)
	{
		delete ppCellAry[i];
	}
	delete[] ppCellAry;
}

/// <summary>
/// ������
/// </summary>
template<class T>
bool Morton<T>::Init(unsigned int Level, CellRoomInfo room)
{
	// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
	if (Level>CLINER8TREEMANAGER_MAXLEVEL)return false;

	// �e���x���ł̋�Ԑ����Z�o
	int i;
	m_iPow[0] = 1;
	for (i = 1; i <= CLINER8TREEMANAGER_MAXLEVEL + 1; i++)
	{
		m_iPow[i] = m_iPow[i - 1] * 8;
	}

	// Level���x���i0��_�j�̔z��쐬
	m_dwCellNum = (m_iPow[Level + 1] - 1) / 7;
	ppCellAry = new typename BidirectionalList<T>::RegisterTo*[m_dwCellNum];
	ZeroMemory(ppCellAry, sizeof(typename BidirectionalList<T>::RegisterTo*) * m_dwCellNum);

	// �L���̈��o�^
	m_room = room;
	m_fUnit.x = m_room.width  / (1 << Level);
	m_fUnit.y = m_room.height / (1 << Level);
	m_fUnit.z = m_room.depth  / (1 << Level);

	m_level = Level;

	return true;
}

/// <summary>
/// �r�b�g�����炷
/// </summary>
template<class T>
DWORD Morton<T>::BitSeparateFor3D(BYTE n)
{
	DWORD s = n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	//return (s | (s << 1)) & 0x55555555;
	return s;
}

/// <summary>
/// xyz���烂�[�g���ԍ����Z�o
/// </summary>
template<class T>
DWORD Morton<T>::Get3DMortonOrder(BYTE x, BYTE y, BYTE z)
{
	return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
}

/// <summary>
/// vector3���烂�[�g���ԍ����Z�o
/// </summary>
template<class T>
DWORD Morton<T>::GetPosToMortonOrder(const DirectX::SimpleMath::Vector3& pos)
{
	DWORD morton = Get3DMortonOrder(
		(BYTE)((pos.x - m_room.left)  / m_fUnit.x), 
		(BYTE)((pos.y - m_room.bottom) / m_fUnit.y), 
		(BYTE)((pos.z - m_room.back)  / m_fUnit.z)
	);
	return morton;
}

/// <summary>
/// �Q���_�iMIN�AMAX�j���烂�[�g���ԍ����Z�o
/// </summary>
template<class T>
DWORD Morton<T>::Get2PointMortonOrder(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
{
	DWORD LT = GetPosToMortonOrder(min);
	DWORD RB = GetPosToMortonOrder(max);
	if (LT > m_dwCellNum || RB > m_dwCellNum)
	{
		return 0;
	}

	DWORD buf = RB ^ LT;
	unsigned int shiftLevel = 1;
	for (int i = 0; i < m_level; i++)
	{
		DWORD Check = (buf >> (i * 3)) & 0x7;
		if (Check != 0) shiftLevel = i + 1;
	}
	DWORD spaceNum = RB >> (shiftLevel * 3);
	DWORD addNum = ((m_iPow[m_level - shiftLevel] -1) / 7);
	spaceNum += addNum;

	if (spaceNum > m_dwCellNum)
	{
		return 0xffffffff;
	}

	return spaceNum;
}

/// <summary>
/// ��Ԃ̐���
/// </summary>
template<class T>
bool Morton<T>::CreateNewCell(DWORD Elem)
{
	// �����̗v�f�ԍ�
	while (!ppCellAry[Elem])
	{
		// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
		ppCellAry[Elem] = new typename BidirectionalList<T>::RegisterTo();

		// �e��ԂɃW�����v
		Elem = (Elem - 1) >> 3;
		if (Elem >= m_dwCellNum) break;
	}
	return true;
}

/// <summary>
/// �o�^
/// </summary>
template<class T>
bool Morton<T>::Register(BidirectionalList<T>& collision, const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
{
	if (!&collision) return false;

	// �Y�������v�Z
	DWORD elem = Get2PointMortonOrder(min, max);
	if (elem < m_dwCellNum)
	{
		if (!ppCellAry[elem])
		{
			CreateNewCell(elem);
		}

		ppCellAry[elem]->Add(&collision);

		return true;
	}
	return false;
}

/// <summary>
/// ��Ԃ𔻒肵�ĐڐG���Ă����Ԃ̃��X�g���擾����
/// </summary>
template<class T>
inline DWORD Morton<T>::GetList(std::vector<T*>& colVect)
{
	colVect.clear();
	if (ppCellAry[0] == nullptr) return 0;
	int elem = 0;
	// �����蔻��X�^�b�N���쐬
	std::list<BidirectionalList<T>*> cStack;

	// ���[�g��Ԃ̓����蔻��
	CheckCell(elem, cStack, colVect);

	return (DWORD)colVect.size();
}

template<class T>
inline bool Morton<T>::CheckCell(int elem, std::list<BidirectionalList<T>*>& cStack, std::vector<T*>& colVect)
{
	if (!ppCellAry[elem])return false;

	BidirectionalList<T>* pOFT = ppCellAry[elem]->GetTop();
	BidirectionalList<T>* pNextOFT = nullptr;

	/// <summary>
	/// ��Ԃ̐ڐG�𔻒�A���X�g���쐬����-----------------------------------------------------------------------------------------------
	/// </summary>
	while (pOFT)
	{
		// �X�^�b�N���̃I�u�W�F�N�g�Ɠ����蔻������
		for (std::list<BidirectionalList<T>*>::iterator ite = cStack.begin(); ite != cStack.end(); ite++)
		{
			// �ڐG����Ƃ��ēo�^
			if (&(*ite)->GetElement())
			{
				colVect.push_back(&(pOFT->GetElement()));
				colVect.push_back(&((*ite)->GetElement()));
			}
		}
		// ������ԓ��̃I�u�W�F�N�g�Ɠ����蔻������
		pNextOFT = pOFT->GetNext();
		while (pNextOFT)
		{
			// �ڐG����Ƃ��ēo�^
			colVect.push_back(&(pOFT->GetElement()));
			colVect.push_back(&(pNextOFT->GetElement()));
			pNextOFT = pNextOFT->GetNext();
		}

		pOFT = pOFT->GetNext();
	}

	/// <summary>
	/// ���݂̋�Ԃ̃I�u�W�F�N�g���X�^�b�N�ɒǉ�------------------------------------------------------------------------------------------
	/// </summary>
	int objectNum = 0;
	pOFT = ppCellAry[elem]->GetTop();
	while (pOFT)
	{
		// �X�^�b�N�ɒǉ�
		cStack.push_back(pOFT);

		objectNum++;
		pOFT = pOFT->GetNext();
	}

	/// <summary>
	/// �q�̋�ԂɈړ�---------------------------------------------------------------------------------------------------------------------
	/// </summary>
	bool isChild = false;
	elem = (elem * 8) + 1;
	for (int i = 0; i < 8; i++)
	{
		if (elem < (int)m_dwCellNum &&
			ppCellAry[(elem + i)])
		{
			isChild = true;
			if (!CheckCell((elem + i), cStack, colVect))
			{
				// ���i�q�̋�Ԃł̎q�̑��݁j��������Ȃ������ꍇ,��Ԃ��폜����
				delete ppCellAry[elem + i];
				ppCellAry[elem + i] = nullptr;
			}
		}
	}

	/// <summary>
	/// ���݂̋�Ԃ̃I�u�W�F�N�g���X�^�b�N����폜------------------------------------------------------------------------------------------
	/// </summary>
	for (int i = 0; i < objectNum; i++)
	{
		cStack.pop_back();
	}

	return isChild;
}
