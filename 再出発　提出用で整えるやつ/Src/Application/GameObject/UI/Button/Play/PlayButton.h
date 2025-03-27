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
	//scaleの最大値
	float m_scaleMAX = {};
	//インクリメントする用の定数
	int m_incrmentConst = {};
	//連打防止
	bool m_enterKeyFlg = false;
	//連打防止
	bool m_mouseKeyFlg = false;
};
