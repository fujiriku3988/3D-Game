#pragma once
#include"../../UIBase.h"
class Bad :public UIBase
{
public:
	Bad() {}
	~Bad()override {}

	void Init()override;
	void Update()override;
private:
};
