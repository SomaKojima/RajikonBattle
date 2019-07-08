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
	// ���O��ݒ肷��
	SetName("Stadium");
	SetTag(Tag::Tag_Room);
	// ���f���擾
	ModelData& modelData = TitleRoomModel::GetInstace();
	// 3D���f���`��̃R���|�[�l���g���쐬
	Component* renderThreeDimention = new RenderThreeDimention(modelData.GetModel(), RenderThreeDimention::Type::Sky);
	AddComponent(renderThreeDimention);
	// ���b�V���̓����蔻����쐬
	Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\titleStadium.obj", 600.0f);
	//Component* collisionMesh = new CollisionMesh(L"Resources\\Obj\\Plane.obj", 25.0f);
	AddComponent(collisionMesh);
}
