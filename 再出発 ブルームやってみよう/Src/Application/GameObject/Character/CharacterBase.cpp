#include "CharacterBase.h"
#include"../../Scene/SceneManager.h"

void CharacterBase::Init(const std::string _string)
{
}

void CharacterBase::Init()
{
	m_modelWork = std::make_shared<KdModelWork>();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_pos = { };
	m_scale = { 1 };
	m_spritePos = {};
	m_poly = nullptr;
	m_modelWork = nullptr;
	m_animator = nullptr;
	m_texSize = {};
	m_scaleMat = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;
	m_nodeMat = Math::Matrix::Identity;
	m_rotMatX = Math::Matrix::Identity;
	m_rotMatY = Math::Matrix::Identity;
	m_rotMatZ = Math::Matrix::Identity;
	m_adjustHeight = {};
	m_jumpPow = 0.0f;
	m_jumpVelocity = 0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.0f;
	m_speed = 0.0f;
	m_animeCnt = 0;
	m_animeCntMAX = 0;
	m_anime.count = 0;
	m_anime.speed = 0;
	m_vol.walk = 1.0f;
	m_vol.damage = 1.0f;
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	//画面中央座標
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	//カメラ変数
	m_degAng = {};
	//フラグ
	m_hitFlg = false;
}

void CharacterBase::PreUpdate()
{
}

void CharacterBase::Update()
{
}

void CharacterBase::PostUpdate()
{
}

void CharacterBase::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld,m_color);
	}
}

void CharacterBase::DrawSprite()
{
}

void CharacterBase::GenerateDepthMapFromLight()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
	}
}

void CharacterBase::CollisionGround(const Math::Vector3 _pos, const Math::Vector3 _dir,
	const KdCollider::Type _type, const float _adjust = {}, const float _stepHeight = {})
{
	//レイ判定
	KdCollider::RayInfo ray;
	//飛ばす位置
	ray.m_pos = _pos + Math::Vector3{0,(_adjust),0};
	//長さ
	static const float enableStepHeight = _stepHeight;
	ray.m_range = m_gravity + enableStepHeight;
	//方向
	ray.m_dir = _dir;
	//タイプ
	ray.m_type = _type;
	//当たったOBJの情報を格納するリスト
	std::list<KdCollider::CollisionResult>retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range, kGreenColor);

	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 hitPos = {};

	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit)
	{
		m_pos = hitPos;
		m_gravity = 0;
	}
}

void CharacterBase::CollisionDetection()
{
}

void CharacterBase::AddNode()
{
	
}

