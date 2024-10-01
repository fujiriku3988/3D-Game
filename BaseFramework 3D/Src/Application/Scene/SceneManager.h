﻿#pragma once

class BaseScene;

class SceneManager
{
public:

	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
		GameDevelop,
		GameSales,
		ResultDevelop,
		ResultSales,
	};

	//追加モード
	enum class ModeType
	{
		GameHome,
		GameWork,
	};

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// 次のシーンをセット (次のフレームから切り替わる)
	void SetNextScene(SceneType nextScene)
	{
		m_nextSceneType = nextScene;
	}

	// 現在のシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();

	// 現在のシーンにオブジェクトを追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj);

	SceneType GetSceneType() { return m_currentSceneType; }
	//==========追加===============//

	//モード取ってくるやつ
	ModeType GetModeType() { return m_nowModeType; }
	//モード切り替える奴
	void SetNextMode(ModeType nextMode) { m_nowModeType = nextMode; }

	//ノードリスト追加するやつ
	//void AddNode(const std::shared_ptr<KdModelWork::Node>& node);
	void AddNode(const KdModelWork::Node*& node);

	//const std::list<std::shared_ptr<KdModelWork::Node>>& GetNodeList();
	const std::list<const KdModelWork::Node*>& GetNodeList();

	//==========追加===============//
private:

	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);
	}

	// シーン切り替え関数
	void ChangeScene(SceneType sceneType);

	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::GameDevelop;

	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

	//追加
	ModeType m_nowModeType = ModeType::GameHome;

private:

	SceneManager() { Init(); }
	~SceneManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};
