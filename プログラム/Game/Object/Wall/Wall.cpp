#include "../../../pch.h"
#include "Wall.h"
#include "../../Component/Collision/CollisionMesh.h"
#include "../../Component/Object/Wall/WallReflection.h"

/// <summary>
/// コンストラクタ
/// </summary>
Wall::Wall()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Wall::~Wall()
{
}

/// <summary>
/// 生成
/// </summary>
void Wall::Instance()
{
	// 名前を設定する
	SetName("Wall");
	SetTag(Tag::Tag_Room);
	// メッシュの当たり判定を作成
	Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\Wall.obj", 500.0f);
	AddComponent(collisionMesh);

	// 壁の反射を作成
	Component* wallReflection = new WallReflection();
	AddComponent(wallReflection);
}
