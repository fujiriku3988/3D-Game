#pragma once

// ゲーム上に存在するすべてのオブジェクトの基底となるクラス
class KdGameObject : public std::enable_shared_from_this<KdGameObject>
{
public:

	enum ContainerType
	{
		eNoneCont,
		eMissile,
	};

	//オブジェクトのタイプ宣言
	enum ObjectType
	{
		eNone,
		eBody,
		eParts,
		eProduceParts,
		eConver,
		eContainer,
	};

	// どのような描画を行うのかを設定するTypeID：Bitフラグで複数指定可能
	enum
	{
		eDrawTypeLit = 1 << 0,
		eDrawTypeUnLit = 1 << 1,
		eDrawTypeBright = 1 << 2,
		eDrawTypeUI = 1 << 3,
		eDrawTypeDepthOfShadow = 1 << 4,
	};

	KdGameObject() {}
	virtual ~KdGameObject() { Release(); }

	// 生成される全てに共通するパラメータに対する初期化のみ
	virtual void Init() {}

	virtual void PreUpdate() {}
	virtual void Update() {}
	virtual void PostUpdate() {}

	// それぞれの状況で描画する関数
	virtual void GenerateDepthMapFromLight() {}
	virtual void PreDraw() {}
	virtual void DrawLit() {}
	virtual void DrawUnLit() {}
	virtual void DrawBright() {}
	virtual void DrawSprite() {}

	virtual void DrawDebug();

	virtual void SetAsset(const std::string&) {}

	virtual void SetPos(const Math::Vector3& pos) { m_mWorld.Translation(pos); }
	virtual Math::Vector3 GetPos() const { return m_mWorld.Translation(); }

	// 拡大率を変更する関数
	void SetScale(float scalar);
	virtual void SetScale(const Math::Vector3& scale);
	virtual Math::Vector3 GetScale() const;

	const Math::Matrix& GetMatrix() const { return m_mWorld; }

	virtual bool IsExpired() const { return m_isExpired; }

	virtual bool IsVisible()	const { return false; }
	virtual bool IsRideable()	const { return false; }

	// 視錐台範囲内に入っているかどうか
	virtual bool CheckInScreen(const DirectX::BoundingFrustum&) const { return false; }

	// カメラからの距離を計算
	virtual void CalcDistSqrFromCamera(const Math::Vector3& camPos);

	float GetDistSqrFromCamera() const { return m_distSqrFromCamera; }

	UINT GetDrawType() const { return m_drawType; }

	bool Intersects(const KdCollider::SphereInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults);
	bool Intersects(const KdCollider::BoxInfo& targetBox, std::list<KdCollider::CollisionResult>* pResults);
	bool Intersects(const KdCollider::RayInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults);

	//追加
	//オブジェクトを手に持っているか（true:持ってる false:持ってない）
	void ChangeHoldFlg(bool _flg) { m_holdFlg = _flg; }
	//オブジェクトを投げるか（true:投げる 投げた後自動でfalse）
	void ChangeThrowFlg(bool _flg) { m_throwFlg = _flg; }
	//オブジェクトを付けるか（true:付ける 付けたあと自動でfalse）
	void ChangeAttachFlg(bool _flg) { m_attachFlg = _flg; }
	//（true:付ける 付けたあと自動でfalse）
	void ChangeProdFlg(bool _flg) { m_prodFlg = _flg; }
	//オブジェクトのタイプ
	ObjectType GetObjType() { return m_objType; }
	//ノードの受け取り
	void ReciveNode(const KdModelWork::Node* _node) { m_reciveNode = _node; }
	//オブジェクトの情報受け取り
	void ReciveOBJ(std::shared_ptr<KdGameObject> _obj) { m_wpReciveObj = _obj; }
	//コンテナのタイプ
	ContainerType GetContType() { return m_contType; }
	//コンテナにしまわれてる数miss→KdGameObject
	int PartsHoldNumber() { return m_storeParts; }

	const Math::Matrix GetNodeMatrix()const
	{
		return m_nodeMat;
	}

protected:

	void Release() {}

	// 描画タイプ・何の描画を行うのかを決める / 最適な描画リスト作成用
	UINT m_drawType = 0;

	// カメラからの距離
	float m_distSqrFromCamera = 0;

	// 存在消滅フラグ
	bool m_isExpired = false;

	// 3D空間に存在する機能
	Math::Matrix	m_mWorld;

	// 当たり判定クラス
	std::unique_ptr<KdCollider> m_pCollider = nullptr;

	// デバッグ情報クラス
	std::unique_ptr<KdDebugWireFrame> m_pDebugWire = nullptr;

	//追加変数
	bool m_holdFlg = false;								//手に持ってるか
	bool m_throwFlg = false;							//なげるか
	bool m_attachFlg = false;							//つけるか
	bool m_prodFlg = false;								//生産するか
	ObjectType m_objType;								//オブジェクトタイプ
	const KdModelWork::Node* m_reciveNode = nullptr;	//ノードの情報を受け取るよう
	std::weak_ptr<KdGameObject>m_wpReciveObj;			//オブジェクトの情報受け取るよう
	Math::Matrix m_nodeMat;								//ノード情報格納用
	int m_storeParts;									//コンテナにあるパーツ数
	ContainerType m_contType;							//コンテナに入ってるパーツ
};
