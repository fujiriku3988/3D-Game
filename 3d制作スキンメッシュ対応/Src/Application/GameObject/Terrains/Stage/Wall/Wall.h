#pragma once
#include"../../TerrainBase.h"

class Wall :public TerrainBase
{
public:
	Wall() {}
	~Wall() override {}

	void Init()override;
	void DrawLit()override;

private:
};
