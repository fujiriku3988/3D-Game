#pragma once
#include"../TerrainBase.h"

class Fence :public TerrainBase
{
public:
	Fence() {}
	~Fence() override {}

	void Init()override;
	void Init(const std::string _string)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;

	//状態を切り替えるメソッド
	void ToggleRaise();

private:
	bool m_isRaise = false;// 柵が上がっているかどうかの状態

	void Raise();// 柵を上げる処理
	void Lower();// 柵を下げる処理
};
