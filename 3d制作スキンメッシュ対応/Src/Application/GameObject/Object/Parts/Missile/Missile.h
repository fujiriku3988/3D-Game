#pragma once
#include"../../ObjectBase.h"
class Player;
class Missile :public ObjectBase
{
public:
	Missile() {}
	~Missile() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
private:
};