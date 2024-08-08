﻿#pragma once
class Desk :public KdGameObject
{
public:
	Desk() {}
	~Desk() {}

	void Init()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdModelData>m_model = nullptr;
	Math::Vector3 m_pos;
};