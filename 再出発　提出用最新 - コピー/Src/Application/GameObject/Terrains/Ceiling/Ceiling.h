#pragma once
#include"../../TerrainBase.h"

class Ceiling :public TerrainBase
{
public:
	Ceiling() {}
	~Ceiling() override {}

	void Init()override;
	void DrawLit()override;

private:
};
