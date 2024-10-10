﻿#pragma once
#include"../../ObjectBase.h"
class Player;
class Missile :public ObjectBase
{
public:
	Missile() {}
	~Missile() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void SetPlayer(std::shared_ptr<Player>_player) { m_wpPlayer = _player; }
private:
	std::weak_ptr<Player>m_wpPlayer;
};