#include "BlueBlock.h"

void BlueBlock::Init(const std::string _filePath, int _id)
{
	ObjectBase::Init();

	// オブジェクト名を設定
	m_objName = "BlueBlock" + std::to_string(_id);
	SetName(m_objName);

	//モデルが読み込まれてないなら
	if (m_modelWork == nullptr)
	{
		m_modelWork = std::make_shared<KdModelWork>();
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");
	}

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, m_objName, "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, m_objName, "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, m_objName, "color");
	m_erase = JsonManager::Instance().GetParam<bool>(_filePath, m_objName, "erase");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation(m_animState));

	m_objType = eBlueBlock;

	m_filePath = _filePath;
	m_id = _id;
}

void BlueBlock::DrawLit()
{
	//モデル描画
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void BlueBlock::Update()
{
	//行列を更新
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void BlueBlock::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void BlueBlock::Restart()
{
	//当たり判定を削除（無効化）
	m_pCollider.reset();

	// モデルの再ロードは不要
	m_pos = JsonManager::Instance().GetParamVec3(m_filePath, m_objName, "pos");
	m_scale = JsonManager::Instance().GetParamVec3(m_filePath, m_objName, "scale");
	m_erase = JsonManager::Instance().GetParam<bool>(m_filePath, m_objName, "erase");

	if (m_erase)
	{
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlock/blueBlock.gltf");

		if (!m_pCollider)
		{
			m_pCollider = std::make_unique<KdCollider>();
			m_pCollider->RegisterCollisionShape("BlueBlock", m_modelWork, KdCollider::TypeGround);
		}
		m_pCollider->SetEnable("BlueBlock", true);
	}
	else
	{
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

		if (m_pCollider)
		{
			m_pCollider->SetEnable("BlueBlock", false);
		}
	}
}

void BlueBlock::ToggleErase()
{
	// 状態を反転
	m_erase = !m_erase;

	//// 状態に応じて上げる・下げるアニメーションを再生
	//if (m_erase)
	//{
	//	m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlock/blueBlock.gltf");

	//	//当たり判定を再登録
	//	m_pCollider = std::make_unique<KdCollider>();
	//	m_pCollider->RegisterCollisionShape("BlueBlock", m_modelWork, KdCollider::TypeGround);
	//}
	//else 
	//{
	//	m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

	//	//当たり判定を削除（無効化）
	//	m_pCollider.reset();
	//}

	if (m_erase)
	{
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlock/blueBlock.gltf");

		if (!m_pCollider)
		{
			m_pCollider = std::make_unique<KdCollider>();
			m_pCollider->RegisterCollisionShape("BlueBlock", m_modelWork, KdCollider::TypeGround);
		}
		m_pCollider->SetEnable("BlueBlock", true); // コライダーを有効化
	}
	else
	{
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

		if (m_pCollider)
		{
			m_pCollider->SetEnable("BlueBlock", false); // コライダーを無効化
		}
	}
}