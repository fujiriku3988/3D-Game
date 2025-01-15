#pragma once
#include"../EffectBase.h"
class smoke :public EffectBase
{
public:
	smoke() {};
	~smoke() {};

	void Init(const std::string _filePath)override;
	void Update()override;
	void Restart()override;

private:
	//切り取り範囲
	Math::Vector2 m_split = {};
	int m_uvRect = {};
};
