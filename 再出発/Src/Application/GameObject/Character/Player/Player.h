#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() override{}

	void Init(const std::string _string);
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void AddNode()override;

	void CollisionDetection()override;
private:
	//プレイヤーの動き
	void Action();
	//プレイヤーが当たり判定をして行う処理
	//スフィアの当たり判定
	void CollisionSphere();//後で関数をベースに書いて引数で使いまわせるようにする？

	// 魔法陣の設置
	void SetMagicCircle();

	// テレポート
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
	};
	Math::Vector3 m_magicCirclePos;
	//納品した数
	flgControl m_ctrlFlg;
	std::shared_ptr<KdGameObject> m_holdObj = nullptr;//当たったOBJの情報を保持
	Effekseer::Handle m_magicCircleEffectHandle = -1; // エフェクトのハンド

	// 改造してね
	std::weak_ptr<KdEffekseerObject> m_Eff;
};
