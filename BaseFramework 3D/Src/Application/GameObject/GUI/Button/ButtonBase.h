#pragma once
class CameraBase;
class ButtonBase :public KdGameObject
{
public:
	ButtonBase() {}
	~ButtonBase()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
protected:
	KdTexture m_tex;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	bool m_drawFlg = false;//表示させるかのフラグ（実験用）
	bool m_rotFlg = false;//回転させるときの
	POINT m_Spos;//マウス座標
	std::weak_ptr<CameraBase>m_wpCamera;
};