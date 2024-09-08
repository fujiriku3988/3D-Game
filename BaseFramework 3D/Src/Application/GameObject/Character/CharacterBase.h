#pragma once
class CameraBase;
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

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;
	void GenerateDepthMapFromLight()override;
	void CollisionGround(Math::Vector3 _pos, Math::Vector3 _dir, KdCollider::Type _type, float _adjust);

	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void MoveFlgOn() { m_moveFlg = true; }

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

protected:
	// カメラ回転用マウス座標の差分
	POINT m_FixMousePos{};
	// カメラ回転用角度
	Math::Vector3 m_degAng = Math::Vector3::Zero;
	//モデル用
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::shared_ptr<KdModelWork>m_modelWork = nullptr;
	std::shared_ptr<KdModelData>m_modelData = nullptr;
	//カメラの情報取るよう
	std::weak_ptr<CameraBase>m_wpCamera;
	std::shared_ptr<CameraBase>m_spCamera;
	//２D描画するよう
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	Math::Rectangle m_rect;
	//モデル用の変数
	Math::Vector3 m_pos;
	Math::Vector2 m_spritePos;
	Math::Vector3 m_dir;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_speed;
	float m_gravity;
	float m_gravityPow;
	float m_adjustHeight;
	bool m_hitFlg = false;
	bool m_moveFlg = false;
	//行列
	Math::Matrix scaleMat;
	Math::Matrix transMat;
	Math::Matrix rotationMat;
	Math::Matrix rotMatX;
	Math::Matrix rotMatY;
	Math::Matrix rotMatZ;
	//アニメーション
	AnimetionInfo m_anime;
	int m_animeCnt;
	int m_animeCntMAX;
	//音量
	struct volume
	{
		float walk;
		float damage;
	};
	volume m_vol;
};
