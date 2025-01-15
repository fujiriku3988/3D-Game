#pragma once
class TerrainBase:public KdGameObject
{
public:
	TerrainBase() {};
	~TerrainBase() override{};

	virtual void Init(const std::string _string);
	void Init()override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
protected:
	std::shared_ptr<KdModelData>m_modelData = nullptr;
	std::shared_ptr<KdModelWork>m_modelWork = nullptr;
	Math::Vector3 m_pos;	//座標
	Math::Vector3 m_scale;	//拡縮
	Math::Color m_color;	//色
	Math::Matrix m_transMat;//移動行列
	Math::Matrix m_scaleMat;//拡縮行列
};
