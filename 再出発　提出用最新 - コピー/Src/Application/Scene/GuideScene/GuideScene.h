#pragma once

#include"../BaseScene/BaseScene.h"

class GuideScene : public BaseScene
{
public:

	GuideScene() { Init(); }
	~GuideScene() {}

private:

	void Event() override;
	void Init() override;
	bool m_key = false;//キー制御用
};
