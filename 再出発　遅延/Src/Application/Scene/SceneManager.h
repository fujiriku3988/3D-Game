#pragma once

class BaseScene;

class SceneManager
{
public:

	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
		SettingScene,
		GuideScene,
		StageSelectScene,
		Stage1,
		Stage2,
		Stage3,
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

	//現在のSceneから次のScenenにいく

	SceneType IncrementSceneType(SceneType _currentScene)
	{
		// 列挙型を整数型にキャストして次のシーンに進む
		int nextValue = static_cast<int>(_currentScene) + 1;

		// インクリメント後のシーンを返す
		return static_cast<SceneType>(nextValue);
	}

	//==========追加===============//
private:

	//マネージャーの初期化
	//インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);
	}

	//シーン切り替え関数
	void ChangeScene(SceneType sceneType);

	//現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	//現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Stage3;

	//次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

private:

	SceneManager() { Init(); }
	~SceneManager() {}

public:

	// シングルトンパターン
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};
