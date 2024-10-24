#include "CardBoard.h"
#include"../../../main.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Fade/Fade.h"

void CardBoard::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Structure/CardBoard/CardBoard.gltf");
	m_pos = { 5.0f,1.0f,-5.0f };
	m_scale = { 2.0f };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("CardBoard", m_modelWork, KdCollider::TypeEvent|KdCollider::TypeBump);
	m_objType = eCardBoard;
	m_deliveredLoc = 1;
}

void CardBoard::Update()
{
	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!m_key)
		{
			m_CSVflg = true;
			
			m_key = true;
		}
	}
	else
	{
		m_key = false;
	}

	if (m_CSVflg == true)
	{
		CSVWrite();
		Fade::Instance().BootWhiteFade(SceneManager::SceneType::ResultDevelop);
	}

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = m_scaleMat * m_transMat;

	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("Deliverd:%d\n", m_deliveredNum);
}

void CardBoard::PostUpdate()
{
	
}

void CardBoard::CSVWrite()
{
	std::ifstream ifs("Asset/Data/Delivered.csv");

	if (!ifs.is_open())
	{
		return;//早期リターン
	}

	std::vector<std::string> data;
	std::vector<std::string> dataName;
	std::string linestring;//ファイルから文字列を格納する変数

	//①ファイルから１文字ずつ取ってくる処理
	while (getline(ifs, linestring))
	{

		std::istringstream iss(linestring);//ファイルから取ってきた文字列を操る
		std::string conmaString;//コンマ区切りになった変数を格納

		//②issにある文字列をコンマ区切りにして格納
		while (getline(iss, conmaString, ','))
		{
			data.push_back(conmaString);
		}
	}

	ifs.close();

	std::ofstream ofs("Asset/Data/Delivered.csv");
	//if (m_CSVflg)
	{
		dataName = data;
		for (int i = 0; i < dataName.size(); i++)
		{
			if (i == m_deliveredLoc) { ofs << '\n'; }
			ScoreWrite(data, dataName, "delivered", i, m_deliveredLoc, m_deliveredNum);
			ofs << data[i] << ',';
		}
		//m_CSVflg = false;
	}
	ofs.close();
}

void CardBoard::ScoreWrite(std::vector<std::string>& _data, std::vector<std::string> _dataName, std::string _rankName, int& _i, int _rankNum, int _rank)
{
	if (_dataName[_i] == _rankName)
	{
		_data[_rankNum] = std::to_string(_rank);
	}
}
