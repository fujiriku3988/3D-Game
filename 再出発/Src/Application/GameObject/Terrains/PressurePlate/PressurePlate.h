#pragma once
#include"../TerrainBase.h"

class Fence;
class PressurePlate :public TerrainBase
{
public:
	PressurePlate() {}
	~PressurePlate() override {}

	void Init()override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;

	void SetFence(std::shared_ptr<Fence>_fence) { m_wpFence = _fence; }
private:
	void PlayAnimation();
	bool m_plateUp = true;//true:上がっている,false:下がっている
	bool m_plateDown = false;//true:下がっている,false:上がっている
	int m_plateCT = 0;
	std::weak_ptr<Fence>m_wpFence;
};
