#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class ArmRight :public CharacterBase
{
public:
	ArmRight() {}
	~ArmRight() override {}

	void Init()override;
	void Update()override;

	void OnFlg() { m_flg = true; }
private:
	bool m_flg = false;
};
