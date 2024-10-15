﻿#pragma once
#include"../ObjectBase.h"
#include <memory>
class Player;
class Container;
class ProduceParts :public ObjectBase
{
public:
	ProduceParts() {}
	~ProduceParts() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void Action();

	void SetPlayer(std::shared_ptr<Player>_player) { m_wpPlayer = _player; }
	void SetContainer(std::shared_ptr<Container>_container) { m_wpContainer = _container; }
private:
	std::weak_ptr<Player>m_wpPlayer;
	std::weak_ptr<Container>m_wpContainer;
};