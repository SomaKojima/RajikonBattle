#include "../../pch.h"
#include "GameObject.h"
#include "GameObjectList.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameObjectList::GameObjectList()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameObjectList::~GameObjectList()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void GameObjectList::Initialize()
{
	// 追加のリストを更新
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
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void GameObjectList::Update(float elapsedTime)
{
	// 追加のリストを更新
	while (m_addList.GetTop())
	{
		m_addList.GetTop()->GetElement().Initialize();
		m_list.Add(m_addList.GetTop());
	}

	// リストをマトリクスを更新する
	BidirectionalList<GameObject>* obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().UpdateTransform(elapsedTime);
		obj = obj->GetNext();
	}

	// リストを更新する
	obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().Update(elapsedTime);
		// 削除する場合
		if (obj->GetElement().IsDelete())
		{
			BidirectionalList<GameObject>* buf = obj->GetNext();
			m_deleteList.Add(obj);
			obj = buf;
			continue;
		}
		obj = obj->GetNext();
	}

	// 削除リストの更新する
	BidirectionalList<GameObject>* deleteObj = m_deleteList.GetTop();
	while (deleteObj)
	{
		deleteObj->GetElement().Finalize();
		deleteObj = deleteObj->GetNext();
	}
	m_deleteList.Clear();

}

/// <summary>
/// 描画処理
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
/// 終了処理
/// </summary>
void GameObjectList::Finalize()
{
	// リストの処理
	BidirectionalList<GameObject>* obj = nullptr;
	obj = m_list.GetTop();
	while (obj)
	{
		obj->GetElement().Finalize();
		obj = obj->GetNext();
	}
	m_list.Clear();

	// 削除リストの処理
	BidirectionalList<GameObject>* deleteObj = m_deleteList.GetTop();
	while (deleteObj)
	{
		deleteObj->GetElement().Finalize();
		deleteObj = deleteObj->GetNext();
	}
	m_deleteList.Clear();

	// 追加リストの処理
	BidirectionalList<GameObject>* addObj = m_addList.GetTop();
	while (addObj)
	{
		addObj->GetElement().Finalize();
		addObj = addObj->GetNext();
	}
	m_addList.Clear();
}

/// <summary>
/// 追加リストにゲームオブジェクトを追加する
/// </summary>
/// <param name="gameObject"></param>
void GameObjectList::Add(GameObject * gameObject)
{
	gameObject->Remove();
	m_addList.Add(gameObject);
}

/// <summary>
/// 削除リストにゲームオブジェクトを追加する
/// </summary>
/// <param name="gameObject"></param>
void GameObjectList::Delete(GameObject * gameObject)
{
	gameObject->Remove();
	m_deleteList.Add(gameObject);
}

/// <summary>
/// オブジェクトを検索
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
GameObject * GameObjectList::Find(const char * name)
{
	// リストの処理
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
