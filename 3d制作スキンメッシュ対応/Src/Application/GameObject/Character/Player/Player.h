#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void AddNode()override;
private:
	void Action();
	void UpdateRotateByMouse();
	void CollisionSphere();
	//キー制御用フラグ
	struct KeyFlgControl
	{
		bool Lbuuton = false;
		bool Rbutton = false;
		bool F = false;
		bool E = false;
		bool R = false;
	};
	//納品した数
	KeyFlgControl m_keyFlg;
	std::shared_ptr<KdGameObject> m_holdObj = nullptr;//当たったOBJの情報を保持
};
