#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;
	void Action();
private:
	void UpdateRotateByMouse();
	//キー制御用フラグ
	struct KeyFlgControl
	{
		bool Lbuuton = false;
		bool Rbutton = false;
		bool F = false;
	};
	KeyFlgControl keyFlg;
};
