﻿#pragma once
class CameraBase;
class ObjectBase :public KdGameObject
{
public:
	//アニメーション情報
	struct AnimetionInfo
	{
		float count;//現在のコマ数カウント
		float speed;//アニメーションの速度
	};

	ObjectBase() {}
	~ObjectBase()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;
	void GenerateDepthMapFromLight()override;

	virtual void AddNode();
	//地面当たり判定
	void CollisionGround(Math::Vector3 _pos, Math::Vector3 _dir, KdCollider::Type _type, float _adjust);

	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
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
	//ノード用
	const KdModelWork::Node* m_pNode;
	bool m_addNodeFlg = true;//trueで追加後falseに変換
	//モデル用の変数
	Math::Vector3 m_pos;//座標
	Math::Vector2 m_spritePos;//2D座標
	Math::Vector3 m_dir;//向き
	Math::Vector3 m_rot;//回転値
	Math::Vector3 m_scale;//拡縮値
	Math::Color m_color;//色
	float m_speed;//キャラのスピード
	float m_gravity;//重力
	float m_gravityPow;//重力の力
	float m_adjustHeight;//当たり判定で許容できる段差の高さ
	bool m_hitFlg = false;//当たり判定
	//行列
	Math::Matrix m_scaleMat;//拡縮
	Math::Matrix m_transMat;//移動
	Math::Matrix m_rotationMat;//回転
	Math::Matrix m_rotMatX;//回転X
	Math::Matrix m_rotMatY;//回転Y
	Math::Matrix m_rotMatZ;//回転Z
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