#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() {}

	void Init()override;
	void Update()override;


private:
};
