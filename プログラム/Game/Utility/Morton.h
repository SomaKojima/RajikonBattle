#pragma once
#include "BidirectionalList.h"
#include <list>

/// <summary>
/// 空間情報
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
/// 接触空間情報
/// </summary>
template<class T> class CellInfo
{
public:
	// コンストラクタ
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

	// 初期化
	bool Init(unsigned int Level, CellRoomInfo room);

	// ビットをずらす
	DWORD BitSeparateFor3D(BYTE n);
	// xyzからモートン番号を算出
	DWORD Get3DMortonOrder(BYTE x, BYTE y, BYTE z);
	// vector3からモートン番号を算出
	DWORD GetPosToMortonOrder(const DirectX::SimpleMath::Vector3& pos);
	// ２頂点（MIN、MAX）からモートン番号を算出
	DWORD Get2PointMortonOrder(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max);

	// 空間の生成
	bool CreateNewCell(DWORD Elem);
	// 登録
	bool Register(BidirectionalList<T>& collision, const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max);

	// 空間を判定して接触している空間のリストを取得する
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
/// コンストラクタ
/// </summary>
template<class T>
Morton<T>::Morton()
{
}

/// <summary>
/// デストラクタ
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
/// 初期化
/// </summary>
template<class T>
bool Morton<T>::Init(unsigned int Level, CellRoomInfo room)
{
	// 設定最高レベル以上の空間は作れない
	if (Level>CLINER8TREEMANAGER_MAXLEVEL)return false;

	// 各レベルでの空間数を算出
	int i;
	m_iPow[0] = 1;
	for (i = 1; i <= CLINER8TREEMANAGER_MAXLEVEL + 1; i++)
	{
		m_iPow[i] = m_iPow[i - 1] * 8;
	}

	// Levelレベル（0基点）の配列作成
	m_dwCellNum = (m_iPow[Level + 1] - 1) / 7;
	ppCellAry = new typename BidirectionalList<T>::RegisterTo*[m_dwCellNum];
	ZeroMemory(ppCellAry, sizeof(typename BidirectionalList<T>::RegisterTo*) * m_dwCellNum);

	// 有効領域を登録
	m_room = room;
	m_fUnit.x = m_room.width  / (1 << Level);
	m_fUnit.y = m_room.height / (1 << Level);
	m_fUnit.z = m_room.depth  / (1 << Level);

	m_level = Level;

	return true;
}

/// <summary>
/// ビットをずらす
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
/// xyzからモートン番号を算出
/// </summary>
template<class T>
DWORD Morton<T>::Get3DMortonOrder(BYTE x, BYTE y, BYTE z)
{
	return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
}

/// <summary>
/// vector3からモートン番号を算出
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
/// ２頂点（MIN、MAX）からモートン番号を算出
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
/// 空間の生成
/// </summary>
template<class T>
bool Morton<T>::CreateNewCell(DWORD Elem)
{
	// 引数の要素番号
	while (!ppCellAry[Elem])
	{
		// 指定の要素番号に空間を新規作成
		ppCellAry[Elem] = new typename BidirectionalList<T>::RegisterTo();

		// 親空間にジャンプ
		Elem = (Elem - 1) >> 3;
		if (Elem >= m_dwCellNum) break;
	}
	return true;
}

/// <summary>
/// 登録
/// </summary>
template<class T>
bool Morton<T>::Register(BidirectionalList<T>& collision, const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
{
	if (!&collision) return false;

	// 添え字を計算
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
/// 空間を判定して接触している空間のリストを取得する
/// </summary>
template<class T>
inline DWORD Morton<T>::GetList(std::vector<T*>& colVect)
{
	colVect.clear();
	if (ppCellAry[0] == nullptr) return 0;
	int elem = 0;
	// 当たり判定スタックを作成
	std::list<BidirectionalList<T>*> cStack;

	// ルート空間の当たり判定
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
	/// 空間の接触を判定、リストを作成する-----------------------------------------------------------------------------------------------
	/// </summary>
	while (pOFT)
	{
		// スタック内のオブジェクトと当たり判定を取る
		for (std::list<BidirectionalList<T>*>::iterator ite = cStack.begin(); ite != cStack.end(); ite++)
		{
			// 接触相手として登録
			if (&(*ite)->GetElement())
			{
				colVect.push_back(&(pOFT->GetElement()));
				colVect.push_back(&((*ite)->GetElement()));
			}
		}
		// 同じ空間内のオブジェクトと当たり判定を取る
		pNextOFT = pOFT->GetNext();
		while (pNextOFT)
		{
			// 接触相手として登録
			colVect.push_back(&(pOFT->GetElement()));
			colVect.push_back(&(pNextOFT->GetElement()));
			pNextOFT = pNextOFT->GetNext();
		}

		pOFT = pOFT->GetNext();
	}

	/// <summary>
	/// 現在の空間のオブジェクトをスタックに追加------------------------------------------------------------------------------------------
	/// </summary>
	int objectNum = 0;
	pOFT = ppCellAry[elem]->GetTop();
	while (pOFT)
	{
		// スタックに追加
		cStack.push_back(pOFT);

		objectNum++;
		pOFT = pOFT->GetNext();
	}

	/// <summary>
	/// 子の空間に移動---------------------------------------------------------------------------------------------------------------------
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
				// 孫（子の空間での子の存在）が見つからなかった場合,空間を削除する
				delete ppCellAry[elem + i];
				ppCellAry[elem + i] = nullptr;
			}
		}
	}

	/// <summary>
	/// 現在の空間のオブジェクトをスタックから削除------------------------------------------------------------------------------------------
	/// </summary>
	for (int i = 0; i < objectNum; i++)
	{
		cStack.pop_back();
	}

	return isChild;
}
