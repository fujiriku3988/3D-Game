﻿#pragma once

namespace NumberConstants
{
	//0、1、2などの初期化や割ったりする時によく使う定数
	constexpr int NumZero = 0;
	constexpr auto NumOne = 1;
	constexpr int NumTwo = 2;
	//画面サイズ1280×720
	constexpr int WindowSizeWidth = 640;
	constexpr int WindowSizeHeight = 360;
	//アルファ値の値の定数
	constexpr float AlphaVisible = 1.0f;     //完全に表示
	constexpr float AlphaSemiTransparent = 0.5f; //半透明
}

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
		eGoalPoint,
		eBlueBlock,
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
	//オブジェクトのタイプ
	const ObjectType GetObjType()const { return m_objType; }
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
	Math::Matrix m_mWorld;

	// 当たり判定クラス
	std::unique_ptr<KdCollider> m_pCollider = nullptr;

	// デバッグ情報クラス
	std::unique_ptr<KdDebugWireFrame> m_pDebugWire = nullptr;

	//＝＝＝＝＝＝＝＝＝＝ここから＝＝＝＝＝＝＝＝＝＝＝＝//
	//＝＝＝＝＝＝＝＝＝＝＝＝追加＝＝＝＝＝＝＝＝＝＝＝＝//

	//エフェクトのスピード、サイズ
	//多数必要ならそのクラス内で変数を作る
	float m_effSize = NumberConstants::NumOne;
	float m_effSpeed = NumberConstants::NumOne;

	//オブジェクトタイプ
	ObjectType m_objType = eNone;

	//当たり判定等で使うフラグ
	bool m_hitFlg = false;

	//ファイルのパスを記憶
	std::string m_filePath = "";

	//＝＝＝＝＝＝＝＝＝＝ここまで＝＝＝＝＝＝＝＝＝＝＝＝//
};
