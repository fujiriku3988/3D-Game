#include "Fence.h"
#include"../../../Json/JsonManager.h"

void Fence::Init()
{
	TerrainBase::Init();
	m_modelWork->SetModelData("Asset/Models/Terrain/Fence/Fence2.gltf");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("downStand"));

	////JSONオブジェクトの作成
	//json jsonData;
	//jsonData["Fence1"]["scale"] = 1.0f;
	//// Math::Vector3 の各プロパティを JSON フォーマットに保存
	//jsonData["Fence1"]["pos"]["x"] = -5;
	//jsonData["Fence1"]["pos"]["y"] = 6;
	//jsonData["Fence1"]["pos"]["z"] = 3;

	////JSONファイルへの書き込み
	//std::ofstream file("Asset/Data/Json/Stage1/Fence1.json");
	//if (file.is_open())
	//{
	//	file << jsonData.dump(4); // インデント付きで書き込み
	//	file.close();
	//}

	//m_pos = { -5,6,3 };
	//float scale = JsonManager::Instance().GetParam<float>("Asset/Data/Json/Stage1/Fence1.json", "Fence1", "scale");
	m_pos = JsonManager::Instance().GetParam<Math::Vector3>("Asset/Data/Json/Stage1/Fence1.json", "Fence1", "pos");
	//m_scale = { 1.0f };
	m_color = { 1,1,1,1 };

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Fence", m_modelWork, KdCollider::TypeBump);
	m_objType = eFence;
}

void Fence::Init(const std::string _string)
{
	//m_pos = JsonManager::Instance().GetParam<float>("Asset/Data/data.json", "Player", "Speed");

	
}

void Fence::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void Fence::Update()
{
	//ToggleRaise();

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Fence::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void Fence::ToggleRaise()
{
	// 状態を反転
	m_isRaise = !m_isRaise;

	// 状態に応じて上げる・下げるアニメーションを再生
	if (m_isRaise) 
	{
		Raise();
	}
	else 
	{
		Lower();
	}
}

void Fence::Raise()
{
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"),false);
	if (m_animator->IsAnimationEnd() == true)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"),false);
	}
}

void Fence::Lower()
{
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"),false);
	if (m_animator->IsAnimationEnd() == true)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("downS"),false);
	}
}
