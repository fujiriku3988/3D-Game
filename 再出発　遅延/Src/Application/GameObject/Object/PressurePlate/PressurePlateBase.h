#pragma once
#include"../ObjectBase.h"

class PressurePlateBase :public ObjectBase
{
public:
	PressurePlateBase() {};
	virtual ~PressurePlateBase() override {}

	virtual void Init(const std::string _filePath)override;
	virtual void Init()override;
	virtual void DrawLit()override;
	virtual void Update()override;
	virtual void PostUpdate()override;
	virtual void Restart()override;

protected:
	virtual void PlayAnimation();
	bool m_plateUp = true;//true:上がっている,false:下がっている
	bool m_plateDown = false;//true:下がっている,false:上がっている
	int m_plateCT = {};
};
