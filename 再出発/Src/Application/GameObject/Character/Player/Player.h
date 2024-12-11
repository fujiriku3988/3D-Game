#pragma once
#include"../../../GameObject/Character/CharacterBase.h"
class Player :public CharacterBase
{
public:
	Player() {}
	~Player() override{}

	void Init(const std::string _filePath);
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawUnLit()override;
	void AddNode()override;
	void Restart()override;

	void CollisionDetection()override;
	void PlayerStopON() { m_ctrlFlg.stop = true; }
private:
	//プレイヤーの動き
	void Action();
	//プレイヤーが当たり判定をして行う処理
	 
	
	//スフィアの当たり判定
	void CollisionSphere();//後で関数をベースに書いて引数で使いまわせるようにする？

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
	};
	flgControl m_ctrlFlg;
	//魔法陣の座標
	Math::Vector3 m_magicCirclePos;
	std::shared_ptr<KdGameObject> m_holdObj = nullptr;//当たったOBJの情報を保持

	//エフェクトの情報持つ用
	std::weak_ptr<KdEffekseerObject> m_wpEffect;
};
