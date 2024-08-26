#pragma once

#include"../../BaseScene/BaseScene.h"

class ResultSales : public BaseScene
{
public:

	ResultSales() { Init(); }
	~ResultSales() {}

private:

	void Event() override;
	void Init() override;
};
