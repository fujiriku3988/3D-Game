#include "KdGameObject.h"

void KdGameObject::DrawDebug()
{
	// 早期リターン
	if (!m_pDebugWire)return;

	m_pDebugWire->Draw();
}

void KdGameObject::SetScale(float scalar)
{
	Math::Vector3 scale(scalar);

	SetScale(scale);
}

void KdGameObject::SetScale(const Math::Vector3& scale)
{
	Math::Vector3 vecX = m_mWorld.Right();
	Math::Vector3 vecY = m_mWorld.Up();
	Math::Vector3 vecZ = m_mWorld.Backward(); 
	
	vecX.Normalize();
	vecY.Normalize();
	vecZ.Normalize();

	m_mWorld.Right(vecX * scale.x);
	m_mWorld.Up(vecY * scale.y);
	m_mWorld.Backward(vecZ * scale.z);
}

Math::Vector3 KdGameObject::GetScale() const
{
	return Math::Vector3(m_mWorld.Right().Length(), m_mWorld.Up().Length(), m_mWorld.Backward().Length());
}

void KdGameObject::CalcDistSqrFromCamera(const Math::Vector3& camPos)
{
	m_distSqrFromCamera = (m_mWorld.Translation() - camPos).LengthSquared();
}

bool KdGameObject::Intersects(const KdCollider::SphereInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetShape, m_mWorld, pResults);
}

bool KdGameObject::Intersects(const KdCollider::BoxInfo& targetBox, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetBox, m_mWorld, pResults);
}

bool KdGameObject::Intersects(const KdCollider::RayInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetShape, m_mWorld, pResults);
}

void KdGameObject::AddConnectedPart(std::shared_ptr<KdGameObject> _part)
{
	if (_part && std::find(m_connectedParts.begin(), m_connectedParts.end(), _part) == m_connectedParts.end())
	{
		m_connectedParts.push_back(_part);
	}
}

void KdGameObject::RemoveConnectedPart(std::shared_ptr<KdGameObject> _part)
{
	// リストから指定されたパーツを削除する
	m_connectedParts.erase(std::remove(m_connectedParts.begin(), m_connectedParts.end(), _part),m_connectedParts.end());
}

void KdGameObject::GetAllConnectedParts(std::shared_ptr<KdGameObject> _obj, std::set<std::shared_ptr<KdGameObject>>& _visited)
{
	// すでに訪れたオブジェクトなら処理しない
	if (_visited.find(_obj) != _visited.end()) {
		return;
	}

	// オブジェクトを訪問済みとしてセットに追加
	_visited.insert(_obj);

	// 接続されたすべてのパーツに対して再帰的に探索
	for (auto& part : _obj->GetConnectList()) {
		GetAllConnectedParts(part, _visited);
	}
}

void KdGameObject::Restart()
{
}
