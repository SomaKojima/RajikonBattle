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
/// コンストラクタ
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
	// 変形のゲームオブジェクトを設定する
	m_transform.SetGameObject(this);
}

/// <summary>
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// 初期化
/// </summary>
void GameObject::Initialize()
{
	// 変形の更新
	m_transform.Update(0);

	// コンポーネントの初期化
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Initialize();
	}
	m_childGameObjectList->Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::Update(float elapsedTime)
{
	// コンポーネントの更新
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
/// マトリクスの更新
/// </summary>
/// <param name="elapsedTime"></param>
void GameObject::UpdateTransform(float elapsedTime)
{
	// 変形の更新
	m_transform.Update(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
void GameObject::Render()
{
	// コンポーネントの描画
	for (auto ite = m_componentList.begin(); ite != m_componentList.end(); ite++)
	{
		(*ite)->Render();
	}
	m_childGameObjectList->Render();
}

/// <summary>
/// 終了
/// </summary>
void GameObject::Finalize()
{
	if (GetName() == "Bullet")
	{
		int a = 0;
	}
	// コンポーネントの終了
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
/// 衝突
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
/// 消滅
/// </summary>
void GameObject::Delete()
{
	m_delete = true;
}

/// <summary>
/// 子をリストに追加
/// </summary>
/// <param name="gameObject"></param>
void GameObject::AddChild(GameObject * gameObject)
{
	gameObject->SetParent(this);
	m_childGameObjectList->Add(gameObject);
}

/// <summary>
/// コンポーネントをリストに追加する
/// </summary>
/// <param name="component"></param>
void GameObject::AddComponent(Component * component)
{
	component->SetGameObjec(this);
	m_componentList.push_back(component);
}
