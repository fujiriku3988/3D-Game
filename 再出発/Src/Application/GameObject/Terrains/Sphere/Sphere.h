#pragma once
#include"../TerrainBase.h"

class Sphere :public TerrainBase
{
public:
	Sphere() {}
	~Sphere() override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawBright()override;

private:
	Math::Vector2 m_uvOffset;
};
