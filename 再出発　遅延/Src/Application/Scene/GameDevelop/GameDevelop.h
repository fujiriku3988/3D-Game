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

	//仮
	bool m_key = false;
};
