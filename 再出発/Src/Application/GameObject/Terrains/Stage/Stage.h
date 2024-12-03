#pragma once
#include"../TerrainBase.h"

class Stage :public TerrainBase
{
public:
	Stage() {}
	~Stage() override {}

	void Init()override;
	void Init(const std::string _filePath)override;
	void DrawLit()override;
	
private:
};
