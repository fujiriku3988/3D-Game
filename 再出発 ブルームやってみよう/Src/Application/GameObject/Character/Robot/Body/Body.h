#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class Body :public CharacterBase
{
public:
	Body() {}
	~Body() override {}

	void Init()override;
	void Update()override;

	void OnFlg() { m_flg = true; }
private:
	bool m_flg = false;
};
