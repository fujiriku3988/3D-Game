#pragma once
#include"../../../UIBase.h"
class A :public UIBase
{
public:
	A() {}
	~A()override {}

	void Init()override;
	void Update()override;

private:
};
