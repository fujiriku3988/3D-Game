#pragma once
#include"../../../UIBase.h"
class B :public UIBase
{
public:
	B() {}
	~B()override {}

	void Init()override;
	void Update()override;

private:
};
