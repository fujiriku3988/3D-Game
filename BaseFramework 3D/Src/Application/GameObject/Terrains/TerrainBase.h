#pragma once
class TerrainBase:public KdGameObject
{
public:
	TerrainBase() {};
	~TerrainBase() override{};

	void Init()override;
	void DrawLit()override;
	void Update()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
protected:
	std::shared_ptr<KdModelData>m_modelData = nullptr;
	Math::Vector3 m_pos;
	Math::Vector3 m_scale;
	Math::Color m_color;
	Math::Matrix m_transMat;
};
