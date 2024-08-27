#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class LegRight :public CharacterBase
{
public:
	LegRight() {}
	~LegRight() override {}

	void Init()override;
	void Update()override;
private:
};
