#include "StopBar.h"
#include"../../../../main.h"
#include"../../../../Fade/Fade.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../../GameObject/Character/Robot/Head/Head.h"
#include"../../../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
#include"../../../../GameObject/Character/Robot/ArmRight/ArmRight.h"
#include"../../../../GameObject/Character/Robot/LegLeft/LegLeft.h"
#include"../../../../GameObject/Character/Robot/LegRight/LegRight.h"
#include"../../../..//GameObject/GUI/Bar/DevelopBar/DevelopBar.h"
#include"../../../../GameObject/UI/Text/Bad/Bad.h"
#include"../../../../GameObject/UI/Text/Good/Good.h"
#include"../../../../GameObject/UI/Text/Great/Great.h"
#include"../../../../GameObject/UI/Text/Perfect/Perfect.h"
#include"../../../../GameObject/Camera/CameraBase.h"
#include"../../../../GameObject/GUI/Robot/ArmLeft/ArmLeftGUI.h"
#include"../../../../GameObject/GUI/Robot/ArmRight/ArmRightGUI.h"
#include"../../../../GameObject/GUI/Robot/Body/BodyGUI.h"
#include"../../../../GameObject/GUI/Robot/Head/HeadGUI.h"
#include"../../../../GameObject/GUI/Robot/LegLeft/LegLeftGUI.h"
#include"../../../../GameObject/GUI/Robot/LegRight/LegRightGUI.h"
#include"../../../../GameObject/GUI/Robot/RobotGUIBase.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

void StopBar::Init()
{
	m_pos = { 0,-240 };
	m_stopMove = 1.0f;
	m_speed = { 15.0f,0 };
	m_scale = { 1.0f,1.0f };
	m_time = 60;
	m_step = 0;
	m_wait = 90;
	m_alpha = 1.0f;
	m_tex.Load("Asset/Textures/GUI/Bar/Develop/stopBar.png");
	m_color = { 1,1,1,m_alpha };
	m_stepFlg = false;
	m_resetFlg = false;
	m_keyFlg = false;
	m_resultFlg = false;
	m_qual = eNone;
	m_rank.perfect = 0;
	m_rank.great = 0;
	m_rank.good = 0;
	m_rank.bad = 0;
	m_rank.pefectNum = 4;
	m_rank.greatNum = 5;
	m_rank.goodNum = 6;
	m_rank.badNum = 7;
}

void StopBar::DrawSprite()
{
	m_color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		5 * m_scale.x, 240 * m_scale.y, nullptr, &m_color);
}

void StopBar::Update()
{
	m_pos += m_speed * m_stopMove;
	//バーが端に着いたら動き反転
	if (m_pos.x >= 640 || m_pos.x <= -640)
	{
		m_speed.x *= -1;
	}

	std::shared_ptr<DevelopBar>spDevelopBar = m_wpDevelopBar.lock();
	std::shared_ptr<CameraBase>spCamera = m_wpCamera.lock();
	//ロボGUI
	std::shared_ptr<HeadGUI>spHeadGUI = m_wpHeadGUI.lock();
	std::shared_ptr<BodyGUI>spBodyGUI = m_wpBodyGUI.lock();
	std::shared_ptr<ArmLeftGUI>spArmLeftGUI = m_wpArmLeftGUI.lock();
	std::shared_ptr<ArmRightGUI>spArmRightGUI = m_wpArmRightGUI.lock();
	std::shared_ptr<LegLeftGUI>spLegLeftGUI = m_wpLegLeftGUI.lock();
	std::shared_ptr<LegRightGUI>spLegRightGUI = m_wpLegRightGUI.lock();

	Action();
	MoveParts();
	CountQuality();

	//ミニゲーム終了したら
	if (m_step >= 5)
	{
		m_step = 5;
		m_speed = {};
		m_alpha -= 0.1f;
		m_wait--;
		//表示してるUI消す
		spDevelopBar->aliveFlgOff();
		spHeadGUI->AliveFlgOff();
		spBodyGUI->AliveFlgOff();
		spArmLeftGUI->AliveFlgOff();
		spArmRightGUI->AliveFlgOff();
		spLegLeftGUI->AliveFlgOff();
		spLegRightGUI->AliveFlgOff();
	}

	if (m_resultFlg == true)
	{
		RankingCSV();
		spCamera->SetControlPos({ -5.0f,5.0f,0.0f });
		Fade::Instance().BootWhiteFade(SceneManager::SceneType::ResultDevelop);
	}

	//画像のアルファ値止める
	if (m_alpha <= 0) { m_alpha = 0; }
	//m_waitが０以下にならないように
	if (m_wait <= 0)
	{
		m_wait = 0;
		m_resultFlg = true;
	}

	POINT nowPos;
	GetCursorPos(&nowPos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
	POINT nowLength;

	nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
	nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正

	Application::Instance().m_log.Clear();
	/*Application::Instance().m_log.AddLog("nowPosY:%d\n", nowPos.y);
	Application::Instance().m_log.AddLog("nowPosX:%d\n", nowPos.x);
	Application::Instance().m_log.AddLog("nowLengthY:%d\n", nowLength.y);
	Application::Instance().m_log.AddLog("nowLengthX:%d\n", nowLength.x);*/
	Application::Instance().m_log.AddLog("m_rank.perfect:%d\n", m_rank.perfect);
	Application::Instance().m_log.AddLog("m_rank.great:%d\n", m_rank.great);
	Application::Instance().m_log.AddLog("m_rank.good:%d\n", m_rank.good);
	Application::Instance().m_log.AddLog("m_rank.bad:%d\n", m_rank.bad);
	Application::Instance().m_log.AddLog("m_qual:%d\n", m_qual);

	Application::Instance().m_log.AddLog("m_step:%d\n", m_step);
}

void StopBar::CountQuality()
{
	if (m_qual == ePerfect)
	{
		m_rank.perfect += 1;
		m_qual = eNone;
	}
	if (m_qual == eGreat)
	{
		m_rank.great += 1;
		m_qual = eNone;
	}
	if (m_qual == eGood)
	{
		m_rank.good += 1;
		m_qual = eNone;
	}
	if (m_qual == eBad)
	{
		m_rank.bad += 1;
		m_qual = eNone;
	}
}

void StopBar::Action()
{
	//SPACEで止める
	if (m_time == 60)//今は時間で制御してるけど、ロボのアニメーションが終わったらにしたい
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//キー制御
			if (!m_keyFlg)
			{
				m_keyFlg = true;
				m_resetFlg = true;
				m_stepFlg = true;
				m_stopMove = 0;
				if (m_step < 5)
				{
					//Perfect
					if (m_pos.x >= -30 && m_pos.x <= 30)
					{
						m_qual = ePerfect;
						std::shared_ptr<Perfect> perfect = std::make_shared<Perfect>();
						perfect->Init();
						SceneManager::Instance().AddObject(perfect);
					}
					//Great
					if (m_pos.x >= -120 && m_pos.x <= -31)
					{
						m_qual = eGreat;
						std::shared_ptr<Great> great = std::make_shared<Great>();
						great->Init();
						SceneManager::Instance().AddObject(great);
					}
					else if (m_pos.x >= 31 && m_pos.x <= 120)
					{
						m_qual = eGreat;
						std::shared_ptr<Great> great = std::make_shared<Great>();
						great->Init();
						SceneManager::Instance().AddObject(great);
					}
					//Good
					if (m_pos.x >= -385 && m_pos.x <= -121)
					{
						m_qual = eGood;
						std::shared_ptr<Good> good = std::make_shared<Good>();
						good->Init();
						SceneManager::Instance().AddObject(good);
					}
					else if (m_pos.x >= 121 && m_pos.x <= 385)
					{
						m_qual = eGood;
						std::shared_ptr<Good> good = std::make_shared<Good>();
						good->Init();
						SceneManager::Instance().AddObject(good);
					}
					//Bad
					if (m_pos.x <= -386)
					{
						m_qual = eBad;
						std::shared_ptr<Bad> bad = std::make_shared<Bad>();
						bad->Init();
						SceneManager::Instance().AddObject(bad);
					}
					else if (m_pos.x >= 386)
					{
						m_qual = eBad;
						std::shared_ptr<Bad> bad = std::make_shared<Bad>();
						bad->Init();
						SceneManager::Instance().AddObject(bad);
					}
				}
			}
		}
		else
		{
			m_keyFlg = false;
		}
	}

	//バー止めたら次動き出すまでの時間
	if (m_resetFlg)
	{
		m_time--;
		if (m_time <= 0)//今は時間で制御してるけど、ロボのアニメーションが終わったらにしたい
		{
			m_resetFlg = false;
			m_stopMove = 1.0f;
		}
	}
	else
	{
		m_time = 60;
	}

}

void StopBar::MoveParts()
{
	//ロボモデル
	std::shared_ptr<Head>spHead = m_wpHead.lock();
	std::shared_ptr<ArmLeft>spArmLeft = m_wpArmLeft.lock();
	std::shared_ptr<ArmRight>spArmRight = m_wpArmRight.lock();
	std::shared_ptr<LegLeft>spLegLeft = m_wpLegLeft.lock();
	std::shared_ptr<LegRight>spLegRight = m_wpLegRight.lock();
	//ロボGUI
	std::shared_ptr<HeadGUI>spHeadGUI = m_wpHeadGUI.lock();
	std::shared_ptr<ArmLeftGUI>spArmLeftGUI = m_wpArmLeftGUI.lock();
	std::shared_ptr<ArmRightGUI>spArmRightGUI = m_wpArmRightGUI.lock();
	std::shared_ptr<LegLeftGUI>spLegLeftGUI = m_wpLegLeftGUI.lock();
	std::shared_ptr<LegRightGUI>spLegRightGUI = m_wpLegRightGUI.lock();

	//パーツ動かす処理関連
	if (m_stepFlg)
	{
		m_stepFlg = false;
		m_step += 1;
	}
	//パーツ動かす処理関連
	switch (m_step)
	{
	case 1:
		spHead->MoveFlgOn();
		spHeadGUI->DrawFlgOn();
		break;
	case 2:
		spArmLeft->MoveFlgOn();
		spArmLeftGUI->DrawFlgOn();
		break;
	case 3:
		spArmRight->MoveFlgOn();
		spArmRightGUI->DrawFlgOn();
		break;
	case 4:
		spLegLeft->MoveFlgOn();
		spLegLeftGUI->DrawFlgOn();
		break;
	case 5:
		spLegRight->MoveFlgOn();
		spLegRightGUI->DrawFlgOn();
		break;
	}
}

void StopBar::RankingCSV()
{
	std::ifstream ifs("Asset/Data/a.csv");

	if (!ifs.is_open())
	{
		printf("\n ファイル読み込み失敗\n\n");
		return;//早期リターン
	}

	printf("\n ファイル読み込み成功\n\n");

	std::vector<std::string> data;
	std::vector<std::string> dataName;
	std::string linestring;//ファイルから文字列を格納する変数
	bool headerFlg = true;

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

	std::ofstream ofs("Asset/Data/a.csv");
	if (headerFlg)
	{
		dataName = data;
		for (int i = 0; i < dataName.size(); i++)
		{
			if (i == m_rank.pefectNum) { ofs << '\n'; }
			RankWrite(data, dataName, "perfect", i, m_rank.pefectNum, m_rank.perfect);
			RankWrite(data, dataName, "great", i, m_rank.greatNum, m_rank.great);
			RankWrite(data, dataName, "good", i, m_rank.goodNum, m_rank.good);
			RankWrite(data, dataName, "bad", i, m_rank.badNum, m_rank.bad);
			ofs << data[i] << ',';
		}
		headerFlg = false;
	}
	ofs.close();
}

void StopBar::ExpCSV()
{
	std::ofstream ofs("Asset/Data/Exp.csv");

	/*RankWrite(data, dataName, "perfect", i, m_rank.pefectNum, m_rank.perfect);
	RankWrite(data, dataName, "great", i, m_rank.greatNum, m_rank.great);
	RankWrite(data, dataName, "good", i, m_rank.goodNum, m_rank.good);
	RankWrite(data, dataName, "bad", i, m_rank.badNum, m_rank.bad);*/

	//ofs << data[i] << ',';

	ofs.close();
}

void StopBar::RankWrite(std::vector<std::string>& _data, std::vector<std::string>_dataName, std::string _rankName, int& _i, int _rankNum, int _rank)
{
	if (_dataName[_i] == _rankName)
	{
		_data[_rankNum] = std::to_string(_rank);
	}
}
