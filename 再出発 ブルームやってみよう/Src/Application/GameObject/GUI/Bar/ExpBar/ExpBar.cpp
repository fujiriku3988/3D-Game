#include "ExpBar.h"
#include"../../../../main.h"

void ExpBar::Init()
{
	m_tex1.Load("Asset/Textures/GUI/Bar/Exp/ExpBarMain.png");
	m_tex2.Load("Asset/Textures/GUI/Bar/Exp/ExpBarNull.png");
	m_pos = { -400,-100 };
	m_scale = { 0.5f };
	m_texSizeMain = { 0,89 };
	m_maxSizeMainX = 640;
	m_texSizeNull = { 640,89 };
	m_expPoint = 0;
	m_expPointUp = 1;
	m_pivot = { 0,0.5f };
	m_color = { 1,1,1,1 };
	m_writeFlg = false;
	ExpPointLoad();
	ExpLoad();
}

void ExpBar::DrawSprite()
{
	m_color = { 1,1,1,1 };
	//空のバー
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex2, m_pos.x, m_pos.y,
		m_texSizeNull.x * m_scale.x, m_texSizeNull.y * m_scale.y, nullptr, &m_color, m_pivot);
	//緑のバー
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex1, m_pos.x, m_pos.y,
		m_texSizeMain.x * m_scale.x, m_texSizeMain.y * m_scale.y, nullptr, &m_color, m_pivot);
}

void ExpBar::Update()
{
	//if (m_expPoint <= 0) { m_expPoint = 0; }
	if (m_expPoint > 0)
	{
		m_expPoint -= m_expPointUp;
		m_texSizeMain.x += m_expPointUp;
	}

	if (m_texSizeMain.x >= m_maxSizeMainX) { m_texSizeMain.x = m_maxSizeMainX; }

	if (m_writeFlg)
	{
		ExpWrite();//経験値の取得した状態を保存
	}
}

void ExpBar::ExpPointLoad()
{
	std::ifstream ifs("Asset/Data/Exp.csv");

	if (!ifs.is_open())
	{
		return;//早期リターン
	}

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
			m_expPoint = stoi(conmaString);
		}
	}

	ifs.close();
}

void ExpBar::ExpLoad()
{
	std::ifstream ifs("Asset/Data/ExpBar.csv");

	if (!ifs.is_open())
	{
		return;//早期リターン
	}

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
			m_texSizeMain.x = stoi(conmaString);
		}
	}

	ifs.close();
}

void ExpBar::ExpWrite()
{
	std::ofstream ofs("Asset/Data/ExpBar.csv");

	ofs << m_texSizeMain.x << ',';

	ofs.close();
}
