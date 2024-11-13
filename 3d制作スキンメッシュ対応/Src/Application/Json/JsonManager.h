#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include<json.hpp>
using json = nlohmann::json;

class JsonManager :public KdGameObject
{
public:

	//テンプレート型でデータ型を自動的に解釈する
	template<typename T>

	//変数 = GetParamの形で使う
	T GetParam(std::string _filePath, std::string _name, std::string _key)
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

	//テンプレート型でデータ型を自動的に解釈す
	template <typename T>

	//引数に変数を入れて使う形のやつ
	T SetParam(const std::string _filePath,const std::string _name,const std::string _key, T& _value)
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


