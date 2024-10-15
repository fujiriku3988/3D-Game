#pragma once
class CameraBase;
class Player;
class ProduceParts;//いらんかも
class Container;
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

	//カメラのポインタセット
	void SetCamera(const std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
	//プレイヤーのポインタセット
	void SetPlayer(std::shared_ptr<Player>_player) { m_wpPlayer = _player; }
	//生成器ポインタセット
	void SetProdParts(std::shared_ptr<ProduceParts>_parts) { m_wpProdParts = _parts; }//いらんかも
	//コンテナポインタセット
	void SetContainer(std::shared_ptr<Container>_container) { m_wpContainer = _container; }
	//座標のセット
	void SetPos(const Math::Vector3& _pos) { m_pos = _pos; }
	//拡縮値セット
	void SetScale(const Math::Vector3& _scale) { m_scale = _scale; }
	//回転値セット（X軸）
	void SetRotX(const float& _rot) { m_rot.x = _rot; }
	//回転値セット（Z軸）
	void SetRotZ(const float& _rot) { m_rot.z = _rot; }
	//HitFlgをTrueに
	void HitFlgOn() { m_hitFlg = true; }
protected:
	//モデル用
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::shared_ptr<KdModelWork>m_modelWork = nullptr;
	//カメラの情報取るよう
	std::weak_ptr<CameraBase>m_wpCamera;
	std::shared_ptr<CameraBase>m_spCamera;
	//プレイヤーの情報
	std::weak_ptr<Player>m_wpPlayer;
	std::shared_ptr<Player>m_spPlayer;
	//パーツ生成器の情報
	std::weak_ptr<ProduceParts>m_wpProdParts;//いらんかも
	std::shared_ptr<ProduceParts>m_spProdParts;//いらんかも
	//コンテナの情報
	std::weak_ptr<Container>m_wpContainer;
	std::shared_ptr<Container>m_spContainer;
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
