#pragma once
class Chair :public KdGameObject
{
public:
	Chair() {}
	~Chair() override {}

	void Init()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdModelData>m_model = nullptr;
	Math::Vector3 m_pos;
};
