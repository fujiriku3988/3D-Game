#pragma once
class Head;
class ArmLeft;
class ArmRight;
class LegLeft;
class LegRight;
class StopBar :public KdGameObject
{
public:

	enum Quality
	{
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

	void SetHead(std::weak_ptr<Head>_head) { m_wpHead = _head; }
	void SetArmLeft(std::weak_ptr<ArmLeft>_armL) { m_wpArmLeft = _armL; }
	void SetArmRight(std::weak_ptr<ArmRight>_armR) { m_wpArmRight = _armR; }
	void SetLegLeft(std::weak_ptr<LegLeft>_legL) { m_wpLegLeft = _legL; }
	void SetLegRight(std::weak_ptr<LegRight>_legR) { m_wpLegRight = _legR; }
private:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Vector2 m_speed;//バーのスピード
	float m_stopMove;//バー止めるときに使う
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	int m_time;//バーをどれくらい止めとくか
	int m_step;//バーを何回止めてるか
	bool m_keyFlg = false;
	bool m_stepFlg = false;//表示させるかのフラグ（実験用）
	bool m_resetFlg = false;//バーを止めた時のクールタイム
	std::weak_ptr<Head>m_wpHead;
	std::weak_ptr<ArmLeft>m_wpArmLeft;
	std::weak_ptr<ArmRight>m_wpArmRight;
	std::weak_ptr<LegLeft>m_wpLegLeft;
	std::weak_ptr<LegRight>m_wpLegRight;
};
