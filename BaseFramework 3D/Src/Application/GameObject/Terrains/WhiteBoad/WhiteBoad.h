#pragma once
class WhiteBoad :public KdGameObject
{
public:
	WhiteBoad() {}
	~WhiteBoad() override{}

	void Init()override;
	void DrawLit()override;
	void Update()override;
private:
	std::shared_ptr<KdModelData>m_model = nullptr;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	bool m_key = false;;
};
