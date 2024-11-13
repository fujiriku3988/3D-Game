#pragma once

#include"../../BaseScene/BaseScene.h"

class ResultDevelop : public BaseScene
{
public:

	ResultDevelop() { Init(); }
	~ResultDevelop() {}

private:

	void Event() override;
	void Init() override;
	bool m_key = false;
};
