#pragma once

class CSVLoad:public KdGameObject
{
public:
	void Vector3();
	void Load();

private:
	Math::Vector3 m_pos;
	static const int MapHeight = 4;
	static const int MapWidth = 4;
	int m_data[MapHeight][MapWidth];
private:
	CSVLoad() {};
	~CSVLoad() {};

public:
	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static CSVLoad& Instance()
	{
		static CSVLoad instance;
		return instance;
	}
};