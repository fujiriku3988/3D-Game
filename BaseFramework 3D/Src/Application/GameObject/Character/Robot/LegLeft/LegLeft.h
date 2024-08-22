#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class LegLeft :public CharacterBase
{
public:
	LegLeft() {}
	~LegLeft() override {}

	void Init()override;
	void Update()override;

	void OnFlg() { m_flg = true; }
private:
	bool m_flg = false;
};
