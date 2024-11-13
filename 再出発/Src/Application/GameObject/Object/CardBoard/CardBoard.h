#pragma once
#include"../ObjectBase.h"
class Player;
class CardBoard :public ObjectBase
{
public:

	CardBoard() {}
	~CardBoard() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	
private:
	struct Score
	{
		int delivered;		//納品の数
		int deliveredLoc;	//納品の数の配列での位置
	};
	Score m_score;
	int m_deliveredLoc;	//納品の数の配列での位置

	void CSVWrite();
	//スコアの書き込み
	void ScoreWrite(std::vector<std::string>& _data, std::vector<std::string>_dataName,
		std::string _rankName, int& _i, int _rankNum, int _rank);

	//仮
	bool m_CSVflg = false;
	bool m_key = false;

};