#pragma once
#include"../../ObjectBase.h"
class Player;
class CleanRobot:public ObjectBase
{
public:
	CleanRobot() {}
	~CleanRobot() override{}
	
	void Init()override;
	void Update()override;

	void AddNode()override;

	void SetPlayer(std::shared_ptr<Player>_player) { m_wpPlayer = _player; }
private:
	std::weak_ptr<Player>m_wpPlayer;
};