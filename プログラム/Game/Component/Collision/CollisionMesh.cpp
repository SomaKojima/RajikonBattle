
#include <fstream>
#include "../../pch.h"
#include "CollisionMesh.h"
#include "../../SubGame.h"
#include "../../Collision/CCell.h"
#include "../../Collision/CollisionManager.h"
#include "../../DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="file"></param>
/// <param name="radius"></param>
CollisionMesh::CollisionMesh(wchar_t * file, float radius)
	:
	CollisionComponent(new MyCollisionObject::Mesh()),
	m_file(file),
	m_isFile(false),
	m_radius(radius)
{
	// obj�`���̃t�@�C���ǂݍ���
	std::vector<Vector3> vertexes;
	std::vector<int> indexes;
	std::ifstream ifs(file);
	if (!ifs)
	{
		ifs.close();
		return;
	}
	m_isFile = true;
	std::string str;
	while (getline(ifs, str))
	{
		// ���_
		if (str[0] == 'v')
		{
			Vector3 val;
			sscanf_s(str.data(), "v  %f %f %f", &val.x, &val.y, &val.z);
			vertexes.push_back(val);
		}
		// �C���f�b�N�X
		if (str[0] == 'f')
		{
			int a, b, c;
			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);
			// �O�p�`�̒��_�C���f�b�N�X�ԍ������������܂ޏꍇ�͖�������
			if (a != b && a != c && b != c)
			{
				indexes.push_back(a - 1);
				indexes.push_back(c - 1);
				indexes.push_back(b - 1);
			}
		}
	}
	ifs.close();

	std::list<MyCollisionObject::Triangle*> triangles;
	for (size_t i = 0; i < indexes.size() / 3; i++)
	{
		MyCollisionObject::Triangle* triangle = new MyCollisionObject::Triangle();
		triangle->Set_Triangle(vertexes[indexes[i * 3 + 2]], vertexes[indexes[i * 3 + 1]], vertexes[indexes[i * 3]]);
		triangles.push_back(triangle);
	}
	m_collisionObject->shape.mesh->SetMesh(triangles);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionMesh::~CollisionMesh()
{
}

/// <summary>
/// ������
/// </summary>
void CollisionMesh::Initialize()
{
	CollisionManager& collisionManager = CollisionManager::GetInstace();
	//collisionManager.Add(*m_collisionObject, m_gameObject->GetTag());

	m_collisionObject->SetGameObject(*m_gameObject);
	MyCollisionObject::Mesh* mesh = m_collisionObject->shape.mesh;

	////MyCollisionObject::Mesh* mesh = m_collisionObject->shape.mesh;
	//Vector3 min, max;
	//CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	//for (auto ite = mesh->triangles.begin(); ite != mesh->triangles.end(); ite++)
	//{
	//	(*ite)->SetGameObject(*m_gameObject);
	//	(*ite)->GetMinMaxPos(min, max);
	//	cLiner8TreeManager.Register(*(*ite), min, max);
	//}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionMesh::Update(float elapsedTime)
{
	// ��ԓo�^
	CLiner8TreeManager& cLiner8TreeManager = CLiner8TreeManager::GetInstace();
	Vector3 pos = m_gameObject->GetTransform().WorldPos();
	Vector3 pos1 = Vector3(pos.x - m_radius, pos.y - m_radius, pos.z - m_radius);
	Vector3 pos2 = Vector3(pos.x + m_radius, pos.y + m_radius, pos.z + m_radius);
	cLiner8TreeManager.Register(*m_collisionObject, pos1, pos2);

	/*MyCollisionObject::Mesh* mesh = m_collisionObject->shape.mesh;
	Vector3 min, max;
	for (auto ite = mesh->triangles.begin(); ite != mesh->triangles.end(); ite++)
	{
		(*ite)->SetGameObject(*m_gameObject);
		(*ite)->GetMinMaxPos(min, max);
		cLiner8TreeManager.Register(*(*ite), min, max);
	}*/

}

/// <summary>
/// �x������
/// </summary>
/// <param name="elapsedTime"></param>
void CollisionMesh::LateUpdate(float elapsedTime)
{
}

/// <summary>
/// �`�揈��
/// </summary>
void CollisionMesh::Render()
{
	if (m_obj == nullptr && m_isFile)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugMesh>(SubGame::GetInstace().GetGame()->GetDevice(), m_file);
	}
	if(m_obj)
	{
		Game* game = SubGame::GetInstace().GetGame();
		m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I������
/// </summary>
void CollisionMesh::Finalize()
{
}


void CollisionMesh::OnCollision(GameObject & obj, MyCollisionObject::CollisionObject & collisionObject, DirectX::SimpleMath::Vector3 & hitPos)
{
}
