#include "RankCalc.h"
#include<fstream>
#include<sstream>
#include<string>
#include"../../Scene/SceneManager.h"
void RankCalc::Init()
{
	m_perfect = 0;
	m_great = 0;
	m_good = 0;
	m_bad = 0;
	m_score = 0;
	m_rankCalcFlg = true;
	m_rank.S = 100;
	m_rank.A = 80;
	m_rank.B = 60;
	m_rank.C = 40;
	m_rank.D = 20;
	m_rank.E = 0;
	CSVLoad();
}

void RankCalc::Update()
{
	Ranking();
}

void RankCalc::Ranking()
{
	
}

void RankCalc::CSVLoad()
{
	std::ifstream ifs("Asset/Data/RankCalc.csv");

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
			data.push_back(conmaString);//一番上のデータの名前が入ってる行
		}
	}

	if (headerFlg)
	{
		dataName = data;
		RankLoad(data, dataName, "perfect", m_perfect);
		RankLoad(data, dataName, "great", m_great);
		RankLoad(data, dataName, "good", m_good);
		RankLoad(data, dataName, "bad", m_bad);
		headerFlg = false;
	}
	ifs.close();
}

void RankCalc::RankLoad(std::vector<std::string> _data, std::vector<std::string> _dataName, std::string _rankName, int& _rank)
{
	_dataName = _data;
	for (int i = 0; i < _dataName.size(); i++)
	{
		if (_dataName[i] == _rankName)
		{
			int nextLine = _data.size() / 2;
			_rank = std::stoi(_data[i + nextLine]);
			break;
		}
	}
}
