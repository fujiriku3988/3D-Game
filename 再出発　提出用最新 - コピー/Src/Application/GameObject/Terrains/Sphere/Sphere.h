#pragma once
#include"../TerrainBase.h"

class Sphere :public TerrainBase
{
public:
	Sphere() {}
	~Sphere() override {}

	void Init(const std::string _filePath)override;
	void Update()override;
	void DrawLit()override;

private:
	Math::Vector2 m_uvOffset;
};
