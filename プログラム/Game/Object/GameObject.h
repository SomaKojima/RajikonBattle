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
/// ゲームオブジェクトのクラス
/// </summary>
class GameObject : public BidirectionalList<GameObject>
{
public:
	// コンストラクタ
	GameObject();
	// デストラクタ
	virtual ~GameObject();

public:
	// 生成関数
	virtual void Instance() {};

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// マトリクスの更新
	void UpdateTransform(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
	// 衝突処理
	void OnCollision(GameObject& obj, MyCollisionObject::CollisionObject& col, DirectX::SimpleMath::Vector3 &hitPos);
	// 消滅
	void Delete();

public:
	// 子供をリストに追加する
	void AddChild(GameObject* gameObject);

	// コンポーネントのクラスに追加する
	void AddComponent(Component* component);
	/// <summary>
	/// コンポーネントを取得する関数
	/// </summary>
	std::list<Component*>& GetComponentList() { return m_componentList; }
	template<class T>
	inline T* GetComponent();
	template<class T>
	inline T* GetComponent(Component* component);
	template<class T>
	inline std::list<T*> GetComponentList();

	// 変形の取得
	Transform& GetTransform() { return m_transform; }
	// タグの設定
	void SetTag(Tag tag) { m_tag = tag; }
	// タグの取得
	Tag& GetTag() { return m_tag; }
	// 名前の設定
	void SetName(char* name) { m_name = name; }
	// 名前の取得
	char* GetName() { return m_name; }
	// 削除フラグを取得する
	bool IsDelete() { return m_delete; }

	GameObjectList& GetChildList() { return *m_childGameObjectList; }
	void SetParent(GameObject* parent) { m_parent = parent; }
	GameObject* GetParent() { return m_parent; }

private:
	// 子のゲームオブジェクトのリスト
	GameObjectList* m_childGameObjectList;
	// 親
	GameObject* m_parent;
	// 変形
	Transform m_transform;
	// コンポーネントのリスト
	std::list<Component*> m_componentList;
	// タグ
	Tag m_tag;
	// 名前
	char* m_name;
	// 削除フラグ
	bool m_delete;
};

/// <summary>
/// コンポーネントのリストから一つのコンポーネントを取得する
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
/// 引数のポインタからコンポーネントを取得する
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
/// コンポーネントのリストから複数のコンポーネントをリストで取得する
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
