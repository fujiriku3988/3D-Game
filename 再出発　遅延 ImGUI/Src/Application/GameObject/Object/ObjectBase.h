#pragma once
class ObjectBase :public KdGameObject
{
public:

	ObjectBase() {}
	~ObjectBase()override {};

	virtual void Init(const std::string _filePath);
	virtual void Init(const std::string _filePath,int _id);
	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;
	void GenerateDepthMapFromLight()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	// 位置とスケールをオーバーライド
	Math::Vector3 GetPosition() const override
	{
		return m_pos;
	}
	Math::Vector3 GetScale() const override
	{
		return m_scale;
	}

	// 位置を設定する（オブジェクトの移動）
	void SetPosition(const Math::Vector3& pos) override
	{
		m_pos = pos;
		//UpdateTransform(); // 変更を即座に適用
	}

	// スケールを設定する（オブジェクトのサイズ変更）
	void SetScale(const Math::Vector3& scale) override
	{
		m_scale = scale;
		//UpdateTransform(); // 変更を即座に適用
	}

	// ファイルパスを取得する関数を追加
	std::string GetFilePath() const override { return m_filePath; }
protected:
	std::shared_ptr<KdModelData>m_modelData = nullptr;
	std::shared_ptr<KdModelWork>m_modelWork = nullptr;
	std::shared_ptr<KdAnimator> m_animator = nullptr;
	Math::Vector3 m_pos;	//座標
	Math::Vector3 m_scale;	//拡縮
	Math::Vector3 m_emissive;//エミシブ
	Math::Color m_color;	//色
	std::string m_animState;//アニメーションの状態
	Math::Matrix m_transMat;//移動行列
	Math::Matrix m_scaleMat;//拡縮行列
	std::string m_objName;
	//オブジェクトのID（必要なら）
	int m_id = {};
};
