#pragma once
#include"../TerrainBase.h"

class Stage :public TerrainBase
{
public:
	Stage() {}
	~Stage() override {}

	void Init()override;
	void DrawLit()override;
	
private:
};
