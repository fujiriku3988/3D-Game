#pragma once
class Wall :public KdGameObject
{
public:
	Wall() {}
	~Wall() override {}

	void Init()override;
	void DrawLit()override;
	void Update()override;
private:
	std::shared_ptr<KdModelData>m_model = nullptr;
	Math::Vector3 m_pos;
};
