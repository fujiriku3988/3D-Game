#pragma once

#include"../../BaseScene/BaseScene.h"

class StageScene2 : public BaseScene
{
public :

	StageScene2() { Init(); }
	~StageScene2() {}

private:

	void Event() override;
	void Init() override;
};
