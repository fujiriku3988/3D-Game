#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class ArmLeft :public CharacterBase
{
public:
	ArmLeft() {}
	~ArmLeft() override {}

	void Init()override;
	void Update()override;
private:
};
