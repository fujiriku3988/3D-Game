#pragma once
#include"../../UIBase.h"

//クリア後のゲーム全体を少し暗くするバック背景
class BlackBack :public UIBase
{
public:
	BlackBack() {};
	~BlackBack() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
	
	//画面に表示する用
	void DrawFlgTrue() { m_drawFlg = true; }
	//画面から非表示にする用
	void DrawFlgFalse() { m_drawFlg = false; }
private:
};
