#pragma once
#include"../../ObjectBase.h"
class Player;
class CleanRobot:public ObjectBase
{
public:
	CleanRobot() {}
	~CleanRobot() override{}
	
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void AddNode()override;

private:
};