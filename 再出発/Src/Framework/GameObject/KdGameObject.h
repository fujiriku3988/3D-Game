#pragma once

// ゲーム上に存在するすべてのオブジェクトの基底となるクラス
class KdGameObject : public std::enable_shared_from_this<KdGameObject>
{
public:
	//オブジェクトのタイプ宣言
	enum ObjectType
	{
		eNone,
		ePressurePlate,
		eFence,
		eGoalPoint
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
	virtual void IsExpiredTrue() { m_isExpired = true; }

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

	//＝＝＝＝＝＝＝＝＝＝ここから＝＝＝＝＝＝＝＝＝＝＝＝//
	//＝＝＝＝＝＝＝＝＝＝＝＝追加＝＝＝＝＝＝＝＝＝＝＝＝//

	void HitFlg(bool _flg) { m_hitFlg = _flg; }
	
	//ノードの受け取り
	void ReciveNode(const KdModelWork::Node* _node) { m_reciveNode = _node; }
	//オブジェクトの情報受け渡し
	void ReciveOBJ(std::shared_ptr<KdGameObject> _obj) { m_wpReciveObj = _obj; }

	//オブジェクトのタイプ
	const ObjectType GetObjType()const { return m_objType; }
	//接続状態を管理するリスト
	const std::list<std::shared_ptr<KdGameObject>>& GetConnectList()const { return m_connectedParts; }
	//接続されたパーツの数を取得する
	const int GetConnectedPartsCount() const { return m_connectedParts.size(); }
	//オブジェクトの情報をもらってくる
	const std::weak_ptr<KdGameObject> GetRecieveObj()const { return m_wpReciveObj; }

	//接続されたパーツを追加する関数
	void AddConnectedPart(std::shared_ptr<KdGameObject> _part);
	//接続されたパーツを解除する関数
	void RemoveConnectedPart(std::shared_ptr<KdGameObject> _part);
	//接続されたパーツ全削除
	void RemoveAllConnectedParts() { m_connectedParts.clear(); } // リストの中身を全てクリア
	//接続されたパーツ全てのポインタ取得
	void GetAllConnectedParts(std::shared_ptr<KdGameObject> _obj, std::set<std::shared_ptr<KdGameObject>>& _visited);

	//オブジェクトの状態をリセット
	virtual void Restart();

	//＝＝＝＝＝＝＝＝＝＝ここまで＝＝＝＝＝＝＝＝＝＝＝＝//

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

	//＝＝＝＝＝＝＝＝＝＝ここから＝＝＝＝＝＝＝＝＝＝＝＝//
	//＝＝＝＝＝＝＝＝＝＝＝＝追加＝＝＝＝＝＝＝＝＝＝＝＝//

	const KdModelWork::Node* m_reciveNode = nullptr;//ノードの情報を受け取るよう
	std::weak_ptr<KdGameObject>m_wpReciveObj;//オブジェクトの情報受け取るよう（大体当たり判定で使う）

	std::list<std::shared_ptr<KdGameObject>>m_connectedParts;//接続状態を管理する方法

	ObjectType m_objType = eNone;//オブジェクトタイプ

	bool m_hitFlg = false;//当たった時

	std::string m_filePath = "";//

	//＝＝＝＝＝＝＝＝＝＝ここまで＝＝＝＝＝＝＝＝＝＝＝＝//
};
