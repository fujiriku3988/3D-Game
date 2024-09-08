#pragma once
#include"../CharacterBase.h"
class CleanRobot:public CharacterBase
{
public:
	CleanRobot() {}
	~CleanRobot() override{}
	
	void Init()override;
	void Update()override;
	//キャラベースで読んでる
	//void DrawLit()override;
	//void GenerateDepthMapFromLight()override;

private:

};