#pragma once
class Carpet :public KdGameObject
{
public:
	Carpet() {}
	~Carpet() override {}

	void Init()override;
	void DrawLit()override;
	void Update()override;
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
private:
	std::shared_ptr<KdModelData>m_model = nullptr;
	Math::Vector3 m_pos;
	Math::Vector3 m_scale;
	Math::Color m_color;
};
