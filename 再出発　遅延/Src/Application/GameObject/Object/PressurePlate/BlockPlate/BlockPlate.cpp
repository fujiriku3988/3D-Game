#include "BlockPlate.h"
#include "../../Block/BlueBlock/BlueBlock.h"

void BlockPlate::Init(const std::string _filePath)
{
	ObjectBase::Init();
	m_modelWork->SetModelData("Asset/Models/Object/PressurePlate/BlockPlate/BlockPlate.gltf");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"));

	m_pos = JsonManager::Instance().GetParamVec3(_filePath,"BlockPlate","pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "BlockPlate", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "BlockPlate", "color");
	m_plateCT = JsonManager::Instance().GetParam<float>(_filePath, "BlockPlate", "plateCT");
	m_plateUp = JsonManager::Instance().GetParam<bool>(_filePath, "BlockPlate", "plateUp");
	m_plateDown = JsonManager::Instance().GetParam<bool>(_filePath, "BlockPlate", "plateDown");
	m_hitFlg = false;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("BlockPlate", m_modelWork, KdCollider::TypeEvent);
	m_objType = ePressurePlate;

	m_filePath = _filePath;
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
	PlayAnimation();
	

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
	Init(m_filePath);
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
	//プレートが上に上がってるなら
	if (m_hitFlg)
	{
		
		if (m_plateDown == false)
		{
			//スイッチ踏んだときのSE
			KdAudioManager::Instance().Play("Asset/Sounds/SE/plate.wav", false, KdAudioManager::Instance().GetSEVolume());
			//踏んだときのアニメーション
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"), false);
			for (auto& wpBlock : m_blocks)
			{
				if (std::shared_ptr<BlueBlock>spBlock = wpBlock.lock())
				{
					spBlock->ToggleRaise();
				}
			}
			m_plateDown = true;
		}
	}

	//プレートが下に下りてるなら
	if (m_plateUp == false)
	{
		//押下部分が上がってくるアニメーション
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"), false);
		m_plateUp = true;
	}
	
	if (m_plateDown == true)
	{
		m_plateCT++;
		if (m_plateCT >= plateCoolTime)
		{
			m_hitFlg = false;
			m_plateUp = false;
			m_plateDown = false;
		}
	}
	else
	{
		m_plateCT = NumberConstants::NumZero;
	}
}
