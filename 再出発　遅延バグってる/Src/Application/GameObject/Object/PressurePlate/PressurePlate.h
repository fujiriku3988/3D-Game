#pragma once
#include"../ObjectBase.h"

class Fence;
class PressurePlate :public ObjectBase
{
public:
	PressurePlate() {};
	~PressurePlate() override {}

	void Init()override;
	void Init(const std::string _filePath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;
	void Restart()override;

	void SetFence(std::shared_ptr<Fence>_fence) { m_wpFence = _fence; }
	void AddFence(std::shared_ptr<Fence> _fence);
private:
	void PlayAnimation();
	bool m_plateUp = true;//true:上がっている,false:下がっている
	bool m_plateDown = false;//true:下がっている,false:上がっている
	int m_plateCT = {};
	std::weak_ptr<Fence>m_wpFence;
	std::list<std::weak_ptr<Fence>> m_fences; //関連付けられたフェンスのリスト
};
