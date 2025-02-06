#include "FencePlate.h"
#include "../../Fence/Fence.h"

void FencePlate::Init(const std::string _filePath)
{
	ObjectBase::Init();
	m_modelWork->SetModelData("Asset/Models/Object/PressurePlate/FencePlate/FencePlate.gltf");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"));

	m_pos = JsonManager::Instance().GetParamVec3(_filePath,"FencePlate","pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "FencePlate", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "FencePlate", "color");
	m_plateCT = JsonManager::Instance().GetParam<float>(_filePath, "FencePlate", "plateCT");
	m_plateUp = JsonManager::Instance().GetParam<bool>(_filePath, "FencePlate", "plateUp");
	m_plateDown = JsonManager::Instance().GetParam<bool>(_filePath, "FencePlate", "plateDown");
	m_hitFlg = false;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("FencePlate", m_modelWork, KdCollider::TypeEvent);
	m_objType = ePressurePlate;

	m_filePath = _filePath;
}

void FencePlate::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void FencePlate::Update()
{
	PlayAnimation();
	

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void FencePlate::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void FencePlate::Restart()
{
	Init(m_filePath);
}

void FencePlate::AddFence(std::shared_ptr<Fence> _fence)
{
	if (_fence)
	{
		m_fences.push_back(_fence);
	}
}

void FencePlate::PlayAnimation()
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
			for (auto& wpFence : m_fences)
			{
				if (std::shared_ptr<Fence>spFence = wpFence.lock())
				{
					spFence->ToggleRaise();
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
