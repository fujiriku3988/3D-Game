#include "JsonManager.h"

// Math::Vector3 用の完全特殊化
template <>
Math::Vector3 JsonManager::GetParam<Math::Vector3>(std::string _filePath, std::string _name, std::string _key) {
	std::ifstream file(_filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open file: " + _filePath);
	}

	// JSON の読み込み
	json jsonData;
	file >> jsonData;
	file.close();

	// JSON データから x, y, z を取得
	if (jsonData.contains(_name) && jsonData[_name].contains(_key)) {
		auto& posData = jsonData[_name][_key];
		Math::Vector3 result;
		result.x = posData.value("x", 0.0f); // デフォルト値を 0.0f に設定
		result.y = posData.value("y", 0.0f);
		result.z = posData.value("z", 0.0f);
		return result;
	}
	else 
	{
		throw std::runtime_error("Error: Key '" + _key + "' not found in JSON data.");
	}
}

void JsonManager::AddParam(const std::string& filePath, const std::string& name, const std::string& key, const Math::Vector3& value)
{
	std::ifstream file(filePath);
	json jsonData;

	if (file.is_open()) {
		file >> jsonData;
		file.close();
	}

	// x, y, z のデータを追加
	jsonData[name][key] = {
		{ "x", value.x },
		{ "y", value.y },
		{ "z", value.z }
	};

	// ファイルに書き戻し
	std::ofstream outFile(filePath);
	if (outFile.is_open()) {
		outFile << jsonData.dump(4); // インデントを設定して保存
		outFile.close();
	}
	else 
	{
		throw std::runtime_error("Error: Could not open file for writing: " + filePath);
	}
}
