#pragma once
#include"../ObjectBase.h"
class Player;
class Conver :public ObjectBase
{
public:
	Conver() {}
	~Conver() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void SetCharaBody(std::shared_ptr<ObjectBase>_body) { m_wpCharaBody = _body; }
	void SetPlayer(std::shared_ptr<Player>_player) { m_wpPlayer = _player; }
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
private:
	std::weak_ptr<ObjectBase>m_wpCharaBody;
	std::weak_ptr<Player>m_wpPlayer;
};