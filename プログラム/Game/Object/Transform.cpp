// ファイルの読み込み
#include "../../pch.h"
#include "Transform.h"
#include "../Utility/BidirectionalList.h"
#include "GameObject.h"
#include "GameObjectList.h"

// 名前空間の使用
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Transform::Transform()
	:
	m_worldPos(DirectX::SimpleMath::Vector3::Zero),
	m_worldVel(DirectX::SimpleMath::Vector3::Zero),
	m_worldAccel(DirectX::SimpleMath::Vector3::Zero),
	m_localDir(DirectX::SimpleMath::Quaternion::Identity),
	m_localInvDir(DirectX::SimpleMath::Quaternion::Identity),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_gameObject(nullptr)
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Transform::Initialize()
{
	// マトリクスを更新
	m_worldMatrix = Matrix::CreateFromQuaternion(WorldDir()) * Matrix::CreateTranslation(m_worldPos);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::Update(float elapsedTime)
{
	//　座標の更新
	m_worldVel += m_worldAccel;
	m_worldPos += m_worldVel;

	// マトリクスを更新
	m_worldMatrix = Matrix::CreateFromQuaternion(WorldDir()) * Matrix::CreateTranslation(m_worldPos);

	// 子供のマトリクスを更新
	UpdateChildMatrix(elapsedTime);
}

/// <summary>
/// 子供のマトリクスを更新する
/// </summary>
/// <param name="elapsedTime"></param>
void Transform::UpdateChildMatrix(float elapsedTime)
{
	BidirectionalList<GameObject>* obj = m_gameObject->GetChildList().GetList().GetTop();
	while (obj)
	{
		Transform& transform = obj->GetElement().GetTransform();
		// 座標を更新
		Vector3 pos = transform.WorldPos() + WorldVel();
		transform.WorldPos(pos);
		// マトリクスを更新
		Matrix matrix = Matrix::CreateFromQuaternion(transform.WorldDir()) * Matrix::CreateTranslation(transform.WorldPos());
		transform.WorldMatrix(matrix);

		obj = obj->GetNext();
	}
}

/// <summary>
/// 子供の座標の更新
/// </summary>
/// <param name="pos"></param>
void Transform::UpdateChildPos(DirectX::SimpleMath::Vector3 & pos)
{
	BidirectionalList<GameObject>* obj = m_gameObject->GetChildList().GetList().GetTop();
	while (obj)
	{
		Transform& transform = obj->GetElement().GetTransform();
		// 座標を更新
		transform.WorldPos(transform.WorldPos() + pos);
		transform.UpdateChildPos(pos);

		obj = obj->GetNext();
	}
}

/// <summary>
/// 座標-----------------------------------------------------------------------------------------------------------
/// </summary>

/// <summary>
/// ワールド座標の設定
/// </summary>
/// <param name="pos"></param>
void Transform::WorldPos(const DirectX::SimpleMath::Vector3 & pos)
{
	UpdateChildPos(pos - m_worldPos);
	m_worldPos = pos;
}

/// <summary>
/// ワールド座標の取得
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & Transform::WorldPos()
{
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		return parent.WorldPos() + m_worldPos;
	}
	return m_worldPos;
}


/// <summary>
/// 速度-----------------------------------------------------------------------------------------------------------
/// </summary>

/// <summary>
/// ワールド速度の取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldVel()
{
	return m_worldVel;
}

/// <summary>
/// ワールド速度の設定
/// </summary>
/// <param name="vel"></param>
void Transform::WorldVel(DirectX::SimpleMath::Vector3 & vel)
{
	m_worldVel = vel;
}


/// <summary>
/// 加速度-----------------------------------------------------------------------------------------------------------
/// </summary>

/// <summary>
/// ワールド加速度の取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::WorldAccel()
{
	return m_worldAccel;
}

/// <summary>
/// ワールド加速度の設定
/// </summary>
/// <param name="accel"></param>
void Transform::WorldAccel(DirectX::SimpleMath::Vector3 & accel)
{
	m_worldAccel = accel;
}


/// <summary>
/// 回転-----------------------------------------------------------------------------------------------------------
/// </summary>

DirectX::SimpleMath::Quaternion Transform::LocalDir()
{
	return m_localDir;
}

void Transform::LocalDir(DirectX::SimpleMath::Quaternion & localDir)
{
	m_localDir = localDir;
	m_localDir.Inverse(m_localInvDir);
}

/// <summary>
/// ワールドの向きを取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::WorldDir()
{
	DirectX::SimpleMath::Quaternion q = m_localDir;
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		q = parent.WorldDir() * m_localDir;
	}
	return q;
}

/// <summary>
/// ワールドの向きを設定する
/// </summary>
/// <param name="dir"></param>
void Transform::WorldDir(DirectX::SimpleMath::Quaternion & dir)
{
	m_localDir = dir;
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		m_localDir = dir * parent.WorldInvDir();
	}
	m_localDir.Inverse(m_localInvDir);
}


/// <summary>
/// 逆回転-----------------------------------------------------------------------------------------------------------
/// </summary>

DirectX::SimpleMath::Quaternion Transform::LocalInvDir()
{
	return m_localInvDir;
}

void Transform::LocalInvDir(DirectX::SimpleMath::Quaternion inv)
{
	m_localInvDir = inv;
}

DirectX::SimpleMath::Quaternion Transform::WorldInvDir()
{
	DirectX::SimpleMath::Quaternion q = m_localInvDir;
	if (m_gameObject->GetParent())
	{
		Transform& parent = m_gameObject->GetParent()->GetTransform();
		q = parent.WorldInvDir() * m_localInvDir;
	}
	return q;
}

/// <summary>
/// ローカル座標のマトリクス
/// </summary>
/// <returns></returns>
//DirectX::SimpleMath::Matrix Transform::LocalMatrix()
//{
//	if (m_gameObject->GetParent())
//	{
//		return Matrix::CreateFromQuaternion(LocalDir()) *Matrix::CreateTranslation(LocalPos());
//	}
//	return m_worldMatrix;
//}

/// <summary>
/// from から to までの回転を計算する
/// </summary>
//DirectX::SimpleMath::Quaternion Transform::FromToRotation(DirectX::SimpleMath::Vector3& fromNormalize, DirectX::SimpleMath::Vector3& toNormalize)
//{
//	// 角度を求める
//	float cosine = fromNormalize.Dot(toNormalize);
//	if (cosine > 1.0f) cosine = 1.0f;
//	else if (cosine < -1.0f) cosine = -1.0f;
//
//	float angle = acos(cosine);
//
//	// 軸を求める
//	Vector3 axis = fromNormalize.Cross(toNormalize);
//	if (axis == Vector3::Zero)
//	{
//
//		// fromNormalize と toNormalize が同じか真反対の場合
//		// Vector3::Forward と fromNormalize で現在の回転を求める
//		float cosineOrigin = Vector3::Forward.Dot(fromNormalize);
//		if (cosineOrigin > 1.0f) cosineOrigin = 1.0f;
//		else if (cosineOrigin < -1.0f) cosineOrigin = -1.0f;
//		float angleOrigin = acos(cosineOrigin);
//
//		Vector3 axisOrigin = Vector3::Forward.Cross(fromNormalize);
//
//		if (axisOrigin == Vector3::Zero)
//		{
//			// Vector3::Forward と fromNormalize が同じか真反対の場合
//			// Quaternion::Identity か 180度回転させる
//			if (cosineOrigin == -1.0f)
//			{
//				return Quaternion::CreateFromAxisAngle(Vector3::Up, XMConvertToRadians(180.0f));
//			}
//			else
//			{
//				return Quaternion::Identity;
//			}
//		}
//
//
//		// 現在の回転からクォータニオンを求める
//		Quaternion qOrigin = Quaternion::CreateFromAxisAngle(axisOrigin, angleOrigin);
//
//		if (cosine == -1.0f)
//		{
//			// 180度回転させる
//			axis = fromNormalize.Cross(Vector3::Transform(Vector3::Right, qOrigin));
//			return Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(180.0f));
//		}
//		else
//		{
//			// 現在の回転のクォータニオンを返す
//			return qOrigin;
//		}
//	}
//
//	Quaternion q = Quaternion::CreateFromAxisAngle(axis, angle);
//
//	return q;
//}