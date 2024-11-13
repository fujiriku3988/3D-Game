#pragma once
#include"../../TerrainBase.h"

class PressurePlate :public TerrainBase
{
public:
	PressurePlate() {}
	~PressurePlate() override {}

	void Init()override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;

private:
	void PlayAnimation();
	bool m_plateUp = true;//true:上がっている,false:下がっている
	bool m_plateDown = false;//true:下がっている,false:上がっている
	int m_plateCT = 0;
};
