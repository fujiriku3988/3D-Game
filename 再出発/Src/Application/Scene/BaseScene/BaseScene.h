#pragma once

class BaseScene
{
public :

	BaseScene() { Init(); }
	virtual ~BaseScene() {}

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	
	// オブジェクトリストに追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj)
	{
		m_objList.push_back(obj);
	}

	//ノードリスト追加
	/*void AddNode(const std::shared_ptr<KdGameObject>& node)
	{
		m_nodeList.push_back(node);
	}*/

	/*void AddNode(const std::shared_ptr<KdModelWork::Node>& node)
	{
		m_nodeList.push_back(node);
	}*/

	void AddNode(const KdModelWork::Node* node)
	{
		m_nodeList.push_back(node);
	}

	//const std::list<std::shared_ptr<KdGameObject>>& GetNodeList()const { return m_nodeList; }
	//const std::list<std::shared_ptr<KdModelWork::Node>>& GetNodeList()const { return m_nodeList; }
	const std::list<const KdModelWork::Node*>& GetNodeList()const { return m_nodeList; }
	//const std::list<KdModelWork::Node>& GetNodeList()const { return m_nodeList; }

protected :

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();
	virtual void Init();

	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;

	//ノードリスト
	//std::list<std::shared_ptr<KdGameObject>>m_nodeList
	//std::list<std::shared_ptr<KdModelWork::Node>>m_nodeList;
	std::list<const KdModelWork::Node*>m_nodeList;
};
