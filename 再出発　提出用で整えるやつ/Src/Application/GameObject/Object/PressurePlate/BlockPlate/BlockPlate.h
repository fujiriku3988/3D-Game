#pragma once
#include"../../PressurePlate/PressurePlateBase.h"

class BlueBlock;
class BlockPlate :public PressurePlateBase
{
public:
	BlockPlate() {};
	~BlockPlate() override {}

	void Init(const std::string _filePath, int _id)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;
	void Restart()override;

	void AddBlueBlock(std::shared_ptr<BlueBlock> _block);
private:
	void PlayAnimation()override;
	std::list<std::weak_ptr<BlueBlock>> m_blocks; //関連付けられたブロックのリスト
};
