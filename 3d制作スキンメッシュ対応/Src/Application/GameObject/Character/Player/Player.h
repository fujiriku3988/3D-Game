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
	void AddNode()override;
private:
	void Action();
	void UpdateRotateByMouse();
	//キー制御用フラグ
	struct KeyFlgControl
	{
		bool Lbuuton = false;
		bool Rbutton = false;
		bool F = false;
		bool E = false;
		bool R = false;
	};
	KeyFlgControl m_keyFlg;
	std::shared_ptr<KdGameObject> m_holdObj = nullptr;//当たったOBJの情報を保持
};
