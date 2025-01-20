#pragma once
#include"../TerrainBase.h"

class Stage :public TerrainBase
{
public:
	Stage() {}
	~Stage() override {}

	void Init(const std::string _filePath)override;
	void Init(const std::string _filePath, const std::string _stage);
	void DrawLit()override;
	
private:
};
