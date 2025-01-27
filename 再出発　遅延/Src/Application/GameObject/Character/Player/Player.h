#pragma once
#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class smoke;
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() override{}

	void Init(const std::string _filePath);
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void Restart()override;

	void CollisionDetection()override;
	void PlayerStopON() { m_ctrlFlg.stop = true; }
private:
	//プレイヤーの動き
	void Action();
	void MovementControll();
	//プレイヤーの回転処理
	void Rotation();
	//スフィアの当たり判定
	void CollisionSphere();

	//魔法陣の設置
	void SetMagicCircle();

	//魔法陣の位置へ移動
	void TeleportToMagicCircle();

	//フラグ制御用
	struct flgControl
	{
		bool Lbuuton = false;
		bool Rbutton = false;
		bool F = false;
		bool E = false;
		bool R = false;
		bool Q = false;
		bool space = false;
		bool collision = false;
		bool jump = false;
		bool mgcCircle = false;
		bool reset = false;
		bool stop = false;
		bool move = false;
	};
	flgControl m_ctrlFlg;
	int m_effDelay = {};
	//魔法陣の座標
	Math::Vector3 m_magicCirclePos = {};
	//エフェクシアの情報持つ用
	std::weak_ptr<KdEffekseerObject> m_wpEffekseer;
};
