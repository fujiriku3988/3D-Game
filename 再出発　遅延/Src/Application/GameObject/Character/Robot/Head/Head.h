#pragma once
#include"../../../../GameObject/Character/CharacterBase.h"
class Head :public CharacterBase
{
public:
	Head() {}
	~Head() override {}

	void Init()override;
	void Update()override;
private:
};
