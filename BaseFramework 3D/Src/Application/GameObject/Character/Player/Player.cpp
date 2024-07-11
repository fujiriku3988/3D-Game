#include "Player.h"
#include<fstream>
#include<sstream>
using namespace std;

void Player::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tank/Tank.gltf");
	Load();
}

void Player::Update()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::Load()
{
	std::ifstream ifs("Asset/Data/test.csv");
	if (!ifs.is_open())
	{
		printf("\n ファイル読み込み失敗\n\n");
		return;//早期リターン
	}

	printf("\n ファイル読み込み成功\n\n");

	string linestring;//ファイルから文字列を格納する変数
	int h = 0;//縦カウンタ
	int w = 0;//横カウンタ

	//①ファイルから１文字ずつ取ってくる処理
	while (getline(ifs, linestring))
	{

		istringstream iss(linestring);//ファイルから取ってきた文字列を操る
		string conmaString;//コンマ区切りになった変数を格納

		//②issにある文字列うをコンマ区切りにして格納
		while (getline(iss, conmaString, ','))
		{
			std::sscanf(conmaString.c_str(), "(%f/%f/%f)", &m_pos.x, &m_pos.y, &m_pos.z);
			//m_data[h][w] = stof(conmaString);
			w++;
		}
		w = 0;
		h++;
	}

	ifs.close();
}
