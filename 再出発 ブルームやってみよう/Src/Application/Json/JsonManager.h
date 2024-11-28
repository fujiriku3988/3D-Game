#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include<json.hpp>
using json = nlohmann::json;

class JsonManager 
{
public:

	//テンプレート型でデータ型を自動的に解釈する
	template<typename T>
	//変数 = GetParam()の形で使う
	//JSONファイルからデータを取ってくる関数
	T GetParam(const std::string _filePath, const std::string _name, const std::string _key);

	//Math::Vector2用のGetParam()
	Math::Vector2 GetParamVec2(const std::string _filePath, const std::string _name, const std::string _key);

	//Math::Vector3用のGetParam()
	Math::Vector3 GetParamVec3(const std::string _filePath, const std::string _name, const std::string _key);

	//Math::Vector4用のGetParam()
	Math::Vector4 GetParamVec4(const std::string& _filePath, const std::string& _name, const std::string& _key);

	//テンプレート型でデータ型を自動的に解釈する
	template <typename T>
	//変数をJSONファイルに書き込む関数
	T AddParam(const std::string& _filePath, const std::string& _name, const std::string& _key, const T& _value);

	//Math::Vector2用のJSONに書き込む関数
	void AddParamVec2(const std::string& _filePath, const std::string& _name, const std::string& _key, const Math::Vector2& _value);

	//Math::Vector3用のJSONに書き込む関数
	void AddParamVec3(const std::string& _filePath, const std::string& _name, const std::string& _key, const Math::Vector3& _value);

	//Math::Vector4用のJSONに書き込む関数
	void AddParamVec4(const std::string& _filePath, const std::string& _name, const std::string& _key, const Math::Vector4& _value);

	//テンプレート型でデータ型を自動的に解釈する
	template <typename T>
	//引数に変数を入れて使う形のやつ_valueが値を入れたい変数
	T SetParam(const std::string _filePath, const std::string _name, const std::string _key, T& _value);

private:
	//なにか変数いるならここに追加
private:
	JsonManager() {}
	~JsonManager() {}
public:
	//インスタンス化
	static JsonManager& Instance()
	{
		static JsonManager instance;
		return instance;
	}
};

template<typename T>
inline T JsonManager::GetParam(std::string _filePath, std::string _name, std::string _key)
{
	// ファイルの読み込み
	std::ifstream file(_filePath);
	if (file.is_open())
	{
		std::stringstream ss;

		ss << file.rdbuf();

		file.close();

		json jsonData;

		//エラーが発生する可能性がある箇所
		try
		{
			//JSON形式の文字列を変換
			jsonData = json::parse(ss.str());

			//jsonDataに指定のキーがあるか
			if (jsonData.contains(_name) && jsonData[_name].contains(_key)) {
				return jsonData[_name][_key].get<T>();
			}
			else
			{
				//指定したキーがないなら
				throw std::runtime_error("Error: Key '" + _key + "' not found in JSON data.");
			}
		}
		catch (const json::parse_error& e)
		{
			//エラーが発生した場合の処理
			std::cerr << "JSON parse error: " << e.what() << std::endl;
			throw;
		}
	}
}

template<typename T>
inline T JsonManager::SetParam(const std::string _filePath, const std::string _name, const std::string _key, T& _value)
{
	//ファイルの読み込み
	std::ifstream file(_filePath);
	if (file.is_open())
	{
		std::stringstream ss;

		ss << file.rdbuf();

		file.close();

		json jsonData;

		//エラーが発生する可能性がある箇所
		try
		{
			//JSON形式の文字列を変換
			jsonData = json::parse(ss.str());

			//jsonDataに指定のキーがあるか
			if (jsonData.contains(_name) && jsonData[_name].contains(_key))
			{
				_value = jsonData[_name][_key].get<T>();
			}
			else
			{
				//指定したキーがないなら例外発生
				throw std::runtime_error("Error: Key '" + _key + "' not found in JSON data.");
			}
		}
		catch (const json::parse_error& e)
		{
			//エラーが発生した場合の処理
			std::cerr << "JSON parse error: " << e.what() << std::endl;
			throw;
		}
	}
}

template <typename T>
inline T JsonManager::AddParam(const std::string& filePath, const std::string& name, const std::string& key, const T& value)
{
	std::ifstream file(filePath);
	json jsonData;

	if (file.is_open()) 
	{
		file >> jsonData;
		file.close();
	}

	//新しいデータを追加
	jsonData[name][key] = value;

	//ファイルに書き戻し
	std::ofstream outFile(filePath);
	if (outFile.is_open()) 
	{
		outFile << jsonData.dump(4); //インデントを設定して保存
		outFile.close();
	}
	else 
	{
		throw std::runtime_error("Error: Could not open file for writing: " + filePath);
	}
}