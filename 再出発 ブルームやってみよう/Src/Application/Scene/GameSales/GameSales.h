#pragma once

#include"../BaseScene/BaseScene.h"

class GameSales : public BaseScene
{
public:

	GameSales() { Init(); }
	~GameSales() {}

private:

	void Event() override;
	void Init() override;
};
