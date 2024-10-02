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
	//キー制御用フラグ
	bool keyLbuuton_Flg = false;
	bool keyRbutton_Flg = false;
	bool keyF_Flg = false;
};
