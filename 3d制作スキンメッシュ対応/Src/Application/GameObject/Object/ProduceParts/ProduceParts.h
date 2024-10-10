#pragma once
#include"../ObjectBase.h"
class Player;
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
private:
	std::weak_ptr<Player>m_wpPlayer;
};