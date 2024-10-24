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
	//取り出したら減らす
	void DecreaseParts() { m_storeParts--; }
	//コンテナが何をしまう物なのか
	void SetProdType(ProductionType _type) { m_prodType = _type; }
	//座標位置
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
private:
};