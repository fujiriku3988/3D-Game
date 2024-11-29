#pragma once
class CameraBase;
class ObjectBase;
class CharacterBase :public KdGameObject
{
public:
	//アニメーション情報
	struct AnimetionInfo
	{
		float count;//現在のコマ数カウント
		float speed;//アニメーションの速度
	};

	CharacterBase() {}
	~CharacterBase()override {};

	virtual void Init(const std::string _string);
	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;
	void GenerateDepthMapFromLight()override;

	//地面との当たり判定を作りたい時に使用
	virtual void CollisionGround(const Math::Vector3 _pos, const Math::Vector3 _dir,
						 const KdCollider::Type _type, const float _adjust, const float _stepHeight);
	virtual void CollisionDetection();

	virtual void AddNode();//ノード追加用

	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void MoveFlgOn() { m_moveFlg = true; }
	void HitFlgOn() { m_hitFlg = true; }

	const Math::Matrix GetRotationMatrix()const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_degAng.y),
			DirectX::XMConvertToRadians(m_degAng.x),
			DirectX::XMConvertToRadians(m_degAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_degAng.y));
	}

	const Math::Matrix GetNodeMatrix()const
	{
		return m_nodeMat;
	}

protected:
	// カメラ回転用マウス座標の差分
	POINT m_FixMousePos{};
	// カメラ回転用角度
	Math::Vector3 m_degAng = Math::Vector3::Zero;
	//モデル
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::shared_ptr<KdModelWork>m_modelWork = nullptr;
	std::shared_ptr<KdAnimator> m_animator = nullptr;
	//カメラの情報取るようweak_ptr→shared_ptr
	std::weak_ptr<CameraBase>m_wpCamera;
	std::shared_ptr<CameraBase>m_spCamera;
	//オブジェクトの情報とるようweak_ptr→shared_ptr
	std::weak_ptr<ObjectBase>m_wpObj;
	std::shared_ptr<ObjectBase>m_spObj;
	//ノード用
	const KdModelWork::Node* m_pNode;
	bool m_addNodeFlg = true;//trueで追加後falseに変換
	//２D描画するよう
	std::shared_ptr<KdTexture> m_tex;
	Math::Vector2 m_texSize;//画像サイズ
	Math::Rectangle m_rect;//切り取り範囲
	Math::Vector2 m_spritePos;//2D座標
	//キャラ用の変数
	Math::Vector3 m_pos;//座標
	Math::Vector3 m_dir;//向き
	Math::Vector3 m_rot;//回転値
	Math::Vector3 m_scale;//拡縮値
	Math::Color m_color;//色
	Math::Vector3 m_adjustHeight;//当たり判定を出す位置の高さの調整
	float m_stepHeight;//当たり判定で許容できる段差の高さ
	float m_speed;//スピード
	float m_jumpPow;//ジャンプ力
	float m_jumpVelocity;//現在のジャンプ速度
	float m_gravity;//重力
	float m_gravityPow;//重力の力
	bool m_hitFlg = false;//当たり判定
	bool m_moveFlg = false;//動いてるかどうか
	//行列
	Math::Matrix m_scaleMat;//拡縮
	Math::Matrix m_transMat;//移動
	Math::Matrix m_rotationMat;//回転
	Math::Matrix m_nodeMat;//ノード情報格納
	Math::Matrix m_rotMatX;//回転X
	Math::Matrix m_rotMatY;//回転Y
	Math::Matrix m_rotMatZ;//回転Z
	//音量
	struct volume
	{
		float walk;
		float jump;
		float damage;
	};
	volume m_vol;
};
