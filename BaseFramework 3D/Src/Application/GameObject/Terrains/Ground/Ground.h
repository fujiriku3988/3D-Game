#pragma once
class Ground :public KdGameObject
{
public:
	Ground() {}
	~Ground() {}

	void Init()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdModelData>m_model = nullptr;
	Math::Vector3 m_pos;
};
