#pragma once
class CleanRobot:public KdGameObject
{
public:
	CleanRobot() {}
	~CleanRobot() override{}
	
	void Init()override;
	void Update()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

private:

};