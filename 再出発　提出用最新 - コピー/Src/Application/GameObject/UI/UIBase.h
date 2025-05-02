#pragma once


class UIBase :public KdGameObject
{
public:
	UIBase() {}
	~UIBase()override {}

	virtual void Init(const std::string _filePath);
	void Init()override;
	void DrawSprite()override;
	void DrawUnLit()override;
	void Update()override;

	void ToggleDraw();
protected:
	//BGM,SEのスライダーの共有で使う
	//ポインターが必要なためここに置く
	static UIBase* m_activeSlider;

	//テクスチャ
	KdTexture m_tex;
	//座標
	Math::Vector2 m_pos;
	//色
	Math::Color m_color;
	//スケール
	Math::Vector2 m_scale;
	//テクスチャサイズ
	Math::Vector2 m_texSize;
	//テクスチャサイズの半分
	Math::Vector2 m_texSizeHarf;
	//描画するか？
	bool m_drawFlg = true;//true:する、false:しない
	//時間
	int m_time = {};
	//アルファ値
	float m_alpha = {};
	//アルファ値の最大値
	float m_alphaMAX = {};
	//アルファ値の最小値
	float m_alphaMIN = {};
};