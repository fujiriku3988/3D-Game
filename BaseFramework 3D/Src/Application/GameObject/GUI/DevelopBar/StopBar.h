#pragma once
class Head;
class ArmLeft;
class ArmRight;
class LegLeft;
class LegRight;
class DevelopBar;
class CameraBase;
class StopBar :public KdGameObject
{
public:

	enum Quality
	{
		eNone,
		ePerfect,
		eGreat,
		eGood,
		eBad,
	};

	Quality m_qual;

	StopBar() {}
	~StopBar()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;
	void CountQuality();
	void Action();
	void MoveParts();
	void CSVLoad();
	void RankWrite(std::vector<std::string>& _data, std::vector<std::string>_dataName,
		std::string _rankName, int& _i, int _rankNum, int _rank);

	void SetHead(std::weak_ptr<Head>_head) { m_wpHead = _head; }
	void SetArmLeft(std::weak_ptr<ArmLeft>_armL) { m_wpArmLeft = _armL; }
	void SetArmRight(std::weak_ptr<ArmRight>_armR) { m_wpArmRight = _armR; }
	void SetLegLeft(std::weak_ptr<LegLeft>_legL) { m_wpLegLeft = _legL; }
	void SetLegRight(std::weak_ptr<LegRight>_legR) { m_wpLegRight = _legR; }
	void SetDevelopBar(std::weak_ptr<DevelopBar>_bar) { m_wpDevelopBar = _bar; }
	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
private:
	struct rank
	{
		int perfect;
		int great;
		int good;
		int bad;
		int pefectNum;
		int greatNum;
		int goodNum;
		int badNum;
	};
	rank m_rank;
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Vector2 m_speed;//バーのスピード
	float m_stopMove;//バー止めるときに使う
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	float m_alpha;//画像のアルファ値
	int m_time;//バーをどれくらい(時間)止めとくか
	int m_step;//バーを何回止めてるか
	int m_wait;//ゲーム終了してからリザルトに移行するまでの時間
	bool m_keyFlg = false;//キー制御
	bool m_stepFlg = false;//表示させるかのフラグ（実験用）
	bool m_resetFlg = false;//バーを止めた時のクールタイム
	bool m_resultFlg = true;//リザルトに移行するフラグ
	std::weak_ptr<Head>m_wpHead;
	std::weak_ptr<ArmLeft>m_wpArmLeft;
	std::weak_ptr<ArmRight>m_wpArmRight;
	std::weak_ptr<LegLeft>m_wpLegLeft;
	std::weak_ptr<LegRight>m_wpLegRight;
	std::weak_ptr<DevelopBar>m_wpDevelopBar;
	std::weak_ptr<CameraBase>m_wpCamera;
};
