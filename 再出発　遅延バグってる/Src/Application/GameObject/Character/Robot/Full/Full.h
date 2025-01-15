#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class Full :public CharacterBase
{
public:
	Full() {}
	~Full() override {}

	void Init()override;
	void Update()override;

	void OnFlg() { m_flg = true; }
private:
	bool m_flg = false;
};
