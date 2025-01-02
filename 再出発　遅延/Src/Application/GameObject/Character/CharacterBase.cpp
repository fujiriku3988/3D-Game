#include "CharacterBase.h"
#include"../../Scene/SceneManager.h"

void CharacterBase::Init()
{
	m_modelWork = std::make_shared<KdModelWork>();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly = nullptr;
	m_modelWork = nullptr;
	m_animator = nullptr;
	m_pos = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "pos");
	m_scale = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "scale");
	m_spritePos = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "sprPos");
	m_texSize = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "texSize");
	m_adjustHeight = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "adjHeight");
	m_jumpPow = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "jumpPow");
	m_jumpVelocity = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "jumpVelocity");
	m_gravity = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "gravity");
	m_gravityPow = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "gravityPow");
	m_speed = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "speed");
	m_vol.walk = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "volWalk");
	m_vol.damage = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "volDamage");
	m_vol.jump = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "volJump");
	m_scaleMat = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;
	m_nodeMat = Math::Matrix::Identity;
	m_rotMatX = Math::Matrix::Identity;
	m_rotMatY = Math::Matrix::Identity;
	m_rotMatZ = Math::Matrix::Identity;
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	//画面中央座標
	m_FixMousePos.x = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "fixMouPosX");
	m_FixMousePos.y = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "fixMouPosY");
	//カメラ変数
	m_degAng = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "degAng");
	//フラグ
	m_hitFlg = JsonManager::Instance().GetParam<bool>("Asset/Data/Json/BaseFile/CharacterBase.json", "CharacterBase", "hitFlg");
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

void CharacterBase::DrawUnLit()
{
}

void CharacterBase::DrawSprite()
{
}

void CharacterBase::GenerateDepthMapFromLight()
{
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

