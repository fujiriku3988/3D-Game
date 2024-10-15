#pragma once
#include"../ObjectBase.h"
class Player;
class Container :public ObjectBase
{
public:

	Container() {}
	~Container() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	//コンテナにしまわれたら増やす
	void IncrementParts() { m_storeParts++; }
	//コンテナが何をしまう物なのか
	void SetContainerType(ContainerType _type) { m_contType = _type; }
	void test(ContainerType _type) { m_contType = _type; }
private:
};