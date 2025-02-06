#pragma once
#include"../../PressurePlate/PressurePlateBase.h"

class Fence;
class FencePlate :public PressurePlateBase
{
public:
	FencePlate() {};
	~FencePlate() override {}

	void Init(const std::string _filePath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;
	void Restart()override;

	void SetFence(std::shared_ptr<Fence>_fence) { m_wpFence = _fence; }
	void AddFence(std::shared_ptr<Fence> _fence);
private:
	void PlayAnimation()override;
	std::weak_ptr<Fence>m_wpFence;
	std::list<std::weak_ptr<Fence>> m_fences; //関連付けられたフェンスのリスト
};
