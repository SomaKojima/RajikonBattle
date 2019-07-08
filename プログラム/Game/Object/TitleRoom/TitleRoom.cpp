#include "../../../pch.h"
#include "TitleRoom.h"
#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Collision/CollisionMesh.h"

#include"../../Data/Model/ModelData.h"

TitleRoom::TitleRoom()
{
}

TitleRoom::~TitleRoom()
{
}

void TitleRoom::Instance()
{
	// 名前を設定する
	SetName("Stadium");
	SetTag(Tag::Tag_Room);
	// モデル取得
	ModelData& modelData = TitleRoomModel::GetInstace();
	// 3Dモデル描画のコンポーネントを作成
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Sky);
	AddComponent(renderThreeDimention);
	// メッシュの当たり判定を作成
	Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\titleStadium.obj", 600.0f);
	//Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\Plane.obj", 25.0f);
	AddComponent(collisionMesh);
}
