#pragma once
class CameraBase;
class Boad:public KdGameObject
{
public:
	Boad() {}
	~Boad()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

	void SetCamera(std::shared_ptr<CameraBase>_camera) { m_wpCamera = _camera; }
private:
	KdTexture m_tex;
	Math::Color m_color;
	bool m_flg = false;
	bool m_rotFlg = false;
	POINT m_Spos;
	std::weak_ptr<CameraBase>m_wpCamera;
};
