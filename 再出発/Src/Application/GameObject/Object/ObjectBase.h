#pragma once
class ObjectBase :public KdGameObject
{
public:

	ObjectBase() {}
	~ObjectBase()override {};

	virtual void Init(const std::string _filePath);
	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;
	void GenerateDepthMapFromLight()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
protected:
	std::shared_ptr<KdModelData>m_modelData = nullptr;
	std::shared_ptr<KdModelWork>m_modelWork = nullptr;
	std::shared_ptr<KdAnimator> m_animator = nullptr;
	Math::Vector3 m_pos;	//座標
	Math::Vector3 m_scale;	//拡縮
	Math::Color m_color;	//色
	std::string m_animState;//アニメーションの状態
	Math::Matrix m_transMat;//移動行列
	Math::Matrix m_scaleMat;//拡縮行列
};
