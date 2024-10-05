#pragma once

class RankCalc :public KdGameObject
{
public:

	RankCalc() {};
	~RankCalc() {};

	void Init()override;
	void Update()override;
	void Ranking();
	void CSVLoad();
	void RankLoad(std::vector<std::string>_data,std::vector<std::string>_dataName, std::string _rankName,int& _rank);

private:
	Math::Vector3 m_pos;
	static const int MapHeight = 4;
	static const int MapWidth = 4;
	int m_data[MapHeight][MapWidth];
	int m_perfect;
	int m_great;
	int m_good;
	int m_bad;
	int m_score;//総合点
	bool m_rankCalcFlg = true;
	struct rank
	{
		int S;
		int A;
		int B;
		int C;
		int D;
		int E;
	};
	rank m_rank;
};