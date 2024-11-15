#pragma once
#include"../../TerrainBase.h"

class WorkBench :public TerrainBase
{
public:
	WorkBench() {}
	~WorkBench() override {}

	void Init()override;
	void DrawLit()override;

private:
};
