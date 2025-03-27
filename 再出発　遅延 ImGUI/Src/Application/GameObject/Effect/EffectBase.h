#pragma once
class CameraBase;

class EffectBase :public KdGameObject
{
public:
	EffectBase() {}
	~EffectBase()override {}

	virtual void Init(const std::string _filePath);
	void Init()override;
	void DrawSprite()override;
	void DrawUnLit()override;
	void Update()override;

	void ToggleDraw();

	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SstScale(Math::Vector3 _scale) { m_scale = _scale; }

protected:
	//アニメーション情報
	struct AnimetionInfo
	{
		float count = {};//現在のコマ数カウント
		float speed = {};//アニメーションの速度
		float MAX = {};//アニメーション最大値
		float MIN = {};//アニメーション最小値
	};
	AnimetionInfo m_anime = {};
	//板ポリ用
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	Math::Vector3 m_pos = {};//座標
	Math::Vector3 m_rot = {};//回転値
	Math::Vector3 m_scale = {};//拡縮値
	//行列
	Math::Matrix m_scaleMat;//拡縮
	Math::Matrix m_transMat;//移動
	Math::Matrix m_rotationMat;//回転
	Math::Matrix m_rotMatX;//回転X
	Math::Matrix m_rotMatY;//回転Y
	Math::Matrix m_rotMatZ;//回転Z
	//２D描画する用
	std::shared_ptr<KdTexture> m_tex = nullptr;
	Math::Vector2 m_sprPos = {};
	Math::Color m_color = {};
	Math::Vector2 m_sprScale = {};
	Math::Vector2 m_texSize = {};
	//その他変数
	bool m_drawFlg = true;
	int m_time = {};
	float m_alpha = {};
	float m_alphaMAX = {};
	float m_alphaMIN = {};
	//カメラの情報取るようweak_ptr→shared_ptr
	std::weak_ptr<CameraBase>m_wpCamera;
};