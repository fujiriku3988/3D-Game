#pragma once
#include"../ObjectBase.h"

class GoalPoint :public ObjectBase
{
public:
	GoalPoint() {}
	~GoalPoint() override {}

	void Init()override;
	void Init(const std::string _filePath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;

private:
};
