#pragma once

#include"../BaseScene/BaseScene.h"

class GameDevelop : public BaseScene
{
public:

	GameDevelop() { Init(); }
	~GameDevelop() {}

private:

	void Event() override;
	void Init() override;
};
