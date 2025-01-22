#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene() {}

private:

	void Event() override;
	void Init() override;
	bool m_key = false;//キー制御用
};
