#pragma once
#include "../Utility/BidirectionalList.h"

class GameObject;

class GOList : public BidirectionalList<GameObject>::RegisterTo
{
};

/// <summary>
/// ゲームオブジェクトのリストクラス
/// </summary>
class GameObjectList
{
public:
	// コンストラクタ
	GameObjectList();
	// デストラクタ
	~GameObjectList();

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
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