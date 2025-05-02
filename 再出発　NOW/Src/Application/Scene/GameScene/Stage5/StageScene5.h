#pragma once

#include"../../BaseScene/BaseScene.h"

class StageScene5 : public BaseScene
{
public :

	StageScene5() { Init(); }
	~StageScene5() {}

private:

	void Event() override;
	void Init() override;
};
