#include "../../../pch.h"
#include "Room.h"
#include "../../Component/Render/RenderThreeDimension.h"
#include "../../Component/Collision/CollisionMesh.h"

#include"../../Data/Model/ModelData.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Instance(Type type)
{
	// ñºëOÇê›íËÇ∑ÇÈ
	SetName("Stadium");
	SetTag(Tag::Tag_Room);

	Component* renderThreeDimention;
	Component* collisionMesh;
	switch (type)
	{
	case Room::Title:
		renderThreeDimention = new RenderThreeDimention(TitleRoom::GetInstace().GetModel(), RenderThreeDimention::Type::Sky);
		collisionMesh = new CollisionMesh(L"Resources\\Obj\\titleStadium.obj", 600.0f);
		break;
	case Room::Play:
		renderThreeDimention = new RenderThreeDimention(RoomModel::GetInstace().GetModel(), RenderThreeDimention::Type::Sky);
		collisionMesh = new CollisionMesh(L"Resources\\Obj\\Stadium.obj", 600.0f);
		break;
	}
	AddComponent(renderThreeDimention);
	AddComponent(collisionMesh);
}
