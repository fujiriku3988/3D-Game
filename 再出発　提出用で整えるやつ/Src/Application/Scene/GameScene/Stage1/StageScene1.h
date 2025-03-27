#pragma once

#include"../../BaseScene/BaseScene.h"

class StageScene1 : public BaseScene
{
public :

	StageScene1() { Init(); }
	~StageScene1() {}

private:

	void Event() override;
	void Init() override;
};
