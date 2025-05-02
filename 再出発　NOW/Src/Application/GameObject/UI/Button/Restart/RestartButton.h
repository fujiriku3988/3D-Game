#pragma once
#include"../../UIBase.h"
class Player;

class RestartButton :public UIBase
{
public:
	RestartButton() {};
	~RestartButton() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;

	//ポインターセット
	void SetPlayer(const std::shared_ptr<Player>& _player);
private:
	//連打防止
	bool m_keyFlg = false;
	//連打防止
	bool m_mouseKeyFlg = false;
	//scaleの最大値
	float m_scaleMAX = {};
	//プレイヤーの情報
	std::weak_ptr<Player>m_wpPlayer;
};
