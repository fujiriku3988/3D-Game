#pragma once
class Player :public KdGameObject
{
public:
	Player() {}
	~Player() {}

	void Init()override;
	void Update()override;
	void DrawLit() override;

	void Load();

private:
	std::shared_ptr<KdModelData>m_model;
	Math::Vector3 m_pos;
};
