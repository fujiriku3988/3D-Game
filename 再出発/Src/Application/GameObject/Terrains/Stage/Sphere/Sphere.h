#pragma once
#include"../../TerrainBase.h"

class Sphere :public TerrainBase
{
public:
	Sphere() {}
	~Sphere() override {}

	void Init()override;
	void DrawLit()override;

private:
};
