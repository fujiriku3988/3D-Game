#include "BlockPlate.h"
#include "../../Block/BlueBlock/BlueBlock.h"

void BlockPlate::Init(const std::string _filePath, int _id)
{
	PressurePlateBase::Init();

	// オブジェクト名を設定
	m_objName = "BlockPlate" + std::to_string(_id);
	SetName(m_objName);

	//モデルが読み込まれてないなら
	if (m_modelWork == nullptr)
	{
		m_modelWork = std::make_shared<KdModelWork>();
		m_modelWork->SetModelData("Asset/Models/Object/PressurePlate/BlockPlate/BlockPlate.gltf");
	}
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"));

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, m_objName, "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, m_objName, "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, m_objName, "color");
	m_plateCT = JsonManager::Instance().GetParam<float>(_filePath, m_objName, "plateCT");
	m_plateFlg = true;
	m_plateAnim = false;
	m_hitFlg = false;

	//コライダーがセットされてないなら
	if (m_pCollider == nullptr)
	{
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("BlockPlate", m_modelWork, KdCollider::TypeEvent);
	}
	m_objType = ePressurePlate;

	m_filePath = _filePath;
	m_id = _id;
}

void BlockPlate::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void BlockPlate::Update()
{
	//アニメーションさせる関数
	PlayAnimation();
	//行列更新
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void BlockPlate::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void BlockPlate::Restart()
{
	//リスタートする時に使う
	Init(m_filePath,m_id);
}

void BlockPlate::AddBlueBlock(std::shared_ptr<BlueBlock> _block)
{
	if (_block)
	{
		m_blocks.push_back(_block);
	}
}

void BlockPlate::PlayAnimation()
{	
	//定数
	constexpr int plateCoolTime = 180;
	if (m_hitFlg)
	{
		// プレートが上がっている場合
		if (m_plateFlg)
		{
			// スイッチ踏んだときのSE
			KdAudioManager::Instance().Play("Asset/Sounds/SE/plate.wav", false, KdAudioManager::Instance().GetSEVolume());

			// 踏んだときのアニメーション
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"), false);

			for (auto& wpBlock : m_blocks)
			{
				if (std::shared_ptr<BlueBlock> spBlock = wpBlock.lock())
				{
					spBlock->ToggleErase();
				}
			}

			m_plateFlg = false;
		}
	}

	// プレートが下がっている場合（m_plateFlgがfalseのとき）
	if (m_plateFlg == false)
	{
		m_plateCT++;
		if (m_plateCT >= plateCoolTime)
		{
			m_hitFlg = false;
			m_plateFlg = true; // クールタイム終了後、プレートを上げる
			m_plateAnim = false; // アニメーションリセット
			m_plateCT = NumberConstants::NumZero;
		}
	}
	else
	{
		// プレートが上がるアニメーションを再生（m_plateFlgがtrueなら）
		if (m_plateAnim == false)
		{
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"), false);
			m_plateAnim = true;
		}
	}
}
