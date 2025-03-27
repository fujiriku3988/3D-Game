#pragma once
#include"../ObjectBase.h"

class PressurePlateBase :public ObjectBase
{
public:
	PressurePlateBase() {};
	virtual ~PressurePlateBase() override {}

	virtual void Init(const std::string _filePath)override;
	virtual void Init()override;
	virtual void DrawLit()override;
	virtual void Update()override;
	virtual void PostUpdate()override;
	virtual void Restart()override;

protected:
	//アニメーションをする関数
	virtual void PlayAnimation();
	//プレートの状態
	bool m_plateFlg = true;//true上がってる、false下がってる
	//プレートのアニメーションの管理用
	bool m_plateAnim = false;
	//プレートが再度機能するのにかかる時間
	int m_plateCT = {};
};
