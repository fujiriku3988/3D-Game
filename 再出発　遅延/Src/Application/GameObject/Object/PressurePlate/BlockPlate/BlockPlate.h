#pragma once
#include"../../ObjectBase.h"

class BlueBlock;

class BlockPlate :public ObjectBase
{
public:
	BlockPlate() {};
	~BlockPlate() override {}

	void Init(const std::string _filePath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;
	void Restart()override;

	void AddBlueBlock(std::shared_ptr<BlueBlock> _block);
private:
	void PlayAnimation();
	bool m_plateUp = true;//true:上がっている,false:下がっている
	bool m_plateDown = false;//true:下がっている,false:上がっている
	int m_plateCT = {};
	std::weak_ptr<BlueBlock>m_wpBlock;
	std::list<std::weak_ptr<BlueBlock>> m_blocks; //関連付けられたブロックのリスト
};
