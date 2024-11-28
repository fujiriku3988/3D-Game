#include "JsonManager.h"

//Math::Vector2用
Math::Vector2 JsonManager::GetParamVec2(std::string _filePath, std::string _name, std::string _key)
{
	std::ifstream file(_filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open file: " + _filePath);
	}

	//JSON の読み込み
	json jsonData;
	file >> jsonData;
	file.close();

	//JSON データから x, yを取得
	if (jsonData.contains(_name) && jsonData[_name].contains(_key)) {
		auto& posData = jsonData[_name][_key];
		Math::Vector2 result;
		result.x = posData.value("x", 0.0f); //デフォルト値を 0.0f に設定
		result.y = posData.value("y", 0.0f);
		return result;
	}
	else
	{
		throw std::runtime_error("Error: Key '" + _key + "' not found in JSON data.");
	}
}

 //Math::Vector3用
Math::Vector3 JsonManager::GetParamVec3(std::string _filePath, std::string _name, std::string _key)
{
	std::ifstream file(_filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open file: " + _filePath);
	}

	//JSON の読み込み
	json jsonData;
	file >> jsonData;
	file.close();

	//JSON データから x, y, zを取得
	if (jsonData.contains(_name) && jsonData[_name].contains(_key)) {
		auto& posData = jsonData[_name][_key];
		Math::Vector3 result;
		result.x = posData.value("x", 0.0f); //デフォルト値を 0.0f に設定
		result.y = posData.value("y", 0.0f);
		result.z = posData.value("z", 0.0f);
		return result;
	}
	else 
	{
		throw std::runtime_error("Error: Key '" + _key + "' not found in JSON data.");
	}
}

//Math::Vector4用
Math::Vector4 JsonManager::GetParamVec4(const std::string& _filePath, const std::string& _name, const std::string& _key)
{
	std::ifstream file(_filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open file: " + _filePath);
	}

	json jsonData;
	file >> jsonData;
	file.close();

	if (jsonData.contains(_name) && jsonData[_name].contains(_key)) {
		auto& posData = jsonData[_name][_key];
		Math::Vector4 result;
		result.x = posData.value("x", 0.0f);
		result.y = posData.value("y", 0.0f);
		result.z = posData.value("z", 0.0f);
		result.w = posData.value("w", 0.0f);
		return result;
	}
	else 
	{
		throw std::runtime_error("Error: Key '" + _key + "' not found in JSON data.");
	}
}

//Math::Vector3用
void JsonManager::AddParamVec2(const std::string& _filePath, const std::string& _name,
	const std::string& _key, const Math::Vector2& _value)
{
	std::ifstream file(_filePath);
	json jsonData;

	if (file.is_open()) 
	{
		file >> jsonData;
		file.close();
	}

	// x, y,のデータを追加
	jsonData[_name][_key] = 
	{
		{ "x", _value.x },
		{ "y", _value.y },
	};

	//ファイルに書き戻し
	std::ofstream outFile(_filePath);
	if (outFile.is_open()) 
	{
		outFile << jsonData.dump(4); //インデントを設定して保存
		outFile.close();
	}
	else
	{
		throw std::runtime_error("Error: Could not open file for writing: " + _filePath);
	}
}

//Math::Vector3用
void JsonManager::AddParamVec3(const std::string& _filePath, const std::string& _name, 
	const std::string& _key, const Math::Vector3& _value)
{
	std::ifstream file(_filePath);
	json jsonData;

	if (file.is_open()) 
	{
		file >> jsonData;
		file.close();
	}

	// x, y, zのデータを追加
	jsonData[_name][_key] = 
	{
		{ "x", _value.x },
		{ "y", _value.y },
		{ "z", _value.z }
	};

	// ファイルに書き戻し
	std::ofstream outFile(_filePath);
	if (outFile.is_open()) 
	{
		outFile << jsonData.dump(4); //インデントを設定して保存
		outFile.close();
	}
	else 
	{
		throw std::runtime_error("Error: Could not open file for writing: " + _filePath);
	}
}
//Math::Vector4用
void JsonManager::AddParamVec4(const std::string& _filePath, const std::string& _name, 
	const std::string& _key, const Math::Vector4& _value)
{
	std::ifstream file(_filePath);
	json jsonData;

	if (file.is_open()) 
	{
		file >> jsonData;
		file.close();
	}

	// x, y, z, wのデータを追加
	jsonData[_name][_key] = 
	{
		{ "x", _value.x },
		{ "y", _value.y },
		{ "z", _value.z },
		{ "w", _value.w }
	};

	//ファイルに書き戻し
	std::ofstream outFile(_filePath);
	if (outFile.is_open()) 
	{
		outFile << jsonData.dump(4); //インデントを設定して保存
		outFile.close();
	}
	else 
	{
		throw std::runtime_error("Error: Could not open file for writing: " + _filePath);
	}
}
