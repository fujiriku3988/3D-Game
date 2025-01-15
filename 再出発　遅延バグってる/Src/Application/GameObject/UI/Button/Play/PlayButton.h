#pragma once
#include"../../UIBase.h"

class PlayButton :public UIBase
{
public:
	PlayButton() {};
	~PlayButton() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
};
