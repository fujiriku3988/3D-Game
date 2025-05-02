#pragma once

#include"../BaseScene/BaseScene.h"

class SettingScene : public BaseScene
{
public:

	SettingScene() { Init(); }
	~SettingScene() {}

private:

	void Event() override;
	void Init() override;
	bool m_key = false;//キー制御用
};
