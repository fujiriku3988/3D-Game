#pragma once
#include"../../TerrainBase.h"

class Tile :public TerrainBase
{
public:
	Tile() {}
	~Tile() override {}

	void Init()override;
	void DrawLit()override;

private:
};
