#pragma once
#include"../../UIBase.h"

class BlackBack :public UIBase
{
public:
	BlackBack() {};
	~BlackBack() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;

	void DrawFlgTrue() { m_drawFlg = true; }
	void DrawFlgFalse() { m_drawFlg = false; }
private:
};
