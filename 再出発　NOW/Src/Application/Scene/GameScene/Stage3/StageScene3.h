#pragma once

#include"../../BaseScene/BaseScene.h"

class StageScene3 : public BaseScene
{
public :

	StageScene3() { Init(); }
	~StageScene3() {}

private:

	void Event() override;
	void Init() override;
};
