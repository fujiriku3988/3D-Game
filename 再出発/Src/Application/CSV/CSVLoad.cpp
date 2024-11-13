#include "CSVLoad.h"
#include<fstream>
#include<sstream>
#include<string>
void CSVLoad::Vector3()
{

}

void CSVLoad::Load()
{
	std::ifstream ifs("Asset/Data/test.csv");
	if (!ifs.is_open())
	{
		printf("\n ファイル読み込み失敗\n\n");
		return;//早期リターン
	}

	printf("\n ファイル読み込み成功\n\n");

	std::string linestring;//ファイルから文字列を格納する変数
	int h = 0;//縦カウンタ
	int w = 0;//横カウンタ

	//①ファイルから１文字ずつ取ってくる処理
	while (getline(ifs, linestring))
	{

		std::istringstream iss(linestring);//ファイルから取ってきた文字列を操る
		std::string conmaString;//コンマ区切りになった変数を格納

		//②issにある文字列をコンマ区切りにして格納
		while (getline(iss, conmaString, ','))
		{
			//if (std::scanf("%s",conmaString) == "m_pos")
			//if (std::sscanf(conmaString.c_str(), "m_pos"))
			{
				//std::sscanf(conmaString.c_str(), "(%f/%f/%f)", &m_pos.x, &m_pos.y, &m_pos.z);
			}

			//m_data[h][w] = stof(conmaString);
			w++;
		}
		w = 0;
		h++;
	}

	ifs.close();
}
