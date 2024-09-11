#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() override{}

	void Init()override;
	void Update()override;
	void Action();
private:
	void UpdateRotateByMouse();
};
