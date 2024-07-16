#pragma once
class AssetManager
{
public:

	void Init();
	void LoadAsset(const std::string name, const std::string filepass);
	

private:
	std::shared_ptr<KdModelWork>m_model;
	std::shared_ptr<KdSquarePolygon>m_poly;
	KdTexture m_tex;
	std::unordered_map<std::string, std::shared_ptr<KdModelWork>> m_asset;
	//std::unordered_map<std::string, std::shared_ptr<KdSquarePolygon>> m_asset;
	//std::unordered_map<std::string, KdTexture> m_asset;

private:

	AssetManager() {}
	~AssetManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static AssetManager& Instance()
	{
		static AssetManager instance;
		return instance;
	}
};