#pragma once
#include"../EffectBase.h"
class smoke :public EffectBase
{
public:
	smoke() {};
	~smoke() {};

	void Init()override;
	void Init(const std::string _filePath)override;
	void Update()override;
	void Restart()override;

private:

};
