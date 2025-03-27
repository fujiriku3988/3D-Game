#include "BlueBlock.h"

void BlueBlock::Init(const std::string _filePath)
{
	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "BlueBlock", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "BlueBlock", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "BlueBlock", "color");
	m_erase = JsonManager::Instance().GetParam<bool>(_filePath, "BlueBlock", "erase");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation(m_animState));

	//m_color = { 1,1,1,0 };

	m_objType = eBlueBlock;

	m_filePath = _filePath;
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
	Init(m_filePath);
	//当たり判定を削除（無効化）
	m_pCollider.reset();
}

void BlueBlock::ToggleErase()
{
	// 状態を反転
	m_erase = !m_erase;

	// 状態に応じて上げる・下げるアニメーションを再生
	if (m_erase)
	{
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlock/blueBlock.gltf");

		//当たり判定を再登録
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("BlueBlock", m_modelWork, KdCollider::TypeGround);
	}
	else 
	{
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

		//当たり判定を削除（無効化）
		m_pCollider.reset();
	}
}