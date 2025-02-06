#include "BlueBlock.h"

void BlueBlock::Init(const std::string _filePath)
{
	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "BlueBlock", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "BlueBlock", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "BlueBlock", "color");
	m_raise = JsonManager::Instance().GetParam<bool>(_filePath, "BlueBlock", "raise");
	m_animState = JsonManager::Instance().GetParam<std::string>(_filePath, "BlueBlock", "animation");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation(m_animState));

	m_objType = eBlueBlock;

	m_filePath = _filePath;
}

void BlueBlock::DrawLit()
{
	//テクスチャのUVTile
	constexpr Math::Vector2 uvTile = { 3,3 };

	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.SetUVTiling(uvTile);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void BlueBlock::Update()
{
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
}

void BlueBlock::ToggleRaise()
{
	// 状態を反転
	m_raise = !m_raise;

	// 状態に応じて上げる・下げるアニメーションを再生
	if (m_raise)
	{
		//Raise();
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlock/blueBlock.gltf");

		//当たり判定を再登録
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("BlueBlock", m_modelWork, KdCollider::TypeGround);
	}
	else 
	{
		//Lower();
		m_modelWork->SetModelData("Asset/Models/Object/Block/BlueBlockFrame/BlueBlockFrame.gltf");

		//当たり判定を削除（または無効化）
		m_pCollider.reset();
	}
}

void BlueBlock::Raise()
{
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"),false);
	if (m_animator->IsAnimationEnd() == true)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"),false);
	}
	KdAudioManager::Instance().Play("Asset/Sounds/SE/BlueBlock.wav", false, KdAudioManager::Instance().GetSEVolume());
}

void BlueBlock::Lower()
{
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"),false);
	if (m_animator->IsAnimationEnd() == true)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("downStand"),false);
	}
	KdAudioManager::Instance().Play("Asset/Data/Sounds/SE/BlueBlock.wav", false, KdAudioManager::Instance().GetSEVolume());
}
