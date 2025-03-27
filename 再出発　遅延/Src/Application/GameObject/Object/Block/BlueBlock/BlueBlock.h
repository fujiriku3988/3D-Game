#pragma once
#include"../../ObjectBase.h"

class BlueBlock :public ObjectBase
{
public:
	BlueBlock() {}
	~BlueBlock() override {}

	void Init(const std::string _filePath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;
	void Restart()override;

	//m_eraseの状態を切り替える
	void ToggleErase();

private:
	//ブロックの透過状態
	bool m_erase = false;//true:消えてない false:消えてる
};
