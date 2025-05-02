#pragma once

#include"../../BaseScene/BaseScene.h"

class StageScene4 : public BaseScene
{
public :

	StageScene4() { Init(); }
	~StageScene4() {}

private:

	void Event() override;
	void Init() override;
};
