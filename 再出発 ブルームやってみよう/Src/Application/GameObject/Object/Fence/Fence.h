﻿#pragma once
#include"../ObjectBase.h"

class Fence :public ObjectBase
{
public:
	Fence() {}
	~Fence() override {}

	void Init()override;
	void Init(const std::string _filepath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;

	//状態を切り替えるメソッド
	void ToggleRaise();

private:
	bool m_raise = false;//true:上がっている false:下がっている

	void Raise();// 柵を上げる処理
	void Lower();// 柵を下げる処理
};
