#include "ImGuiManager.h"
#include "Application/main.h"
#include "Application/Scene/SceneManager.h"

void ImGuiManager::Update()
{
	RegisterObjects();
	//EditObject("BlueBlock");
	EditObjects();

	{
		for (auto&& list : m_UIList)
		{
			list->Update();
		}
	}
}

void ImGuiManager::SetDateUI(const Date& UIdate)
{
	//bool hit = false;
	////名前で探すあったらデータを書き換えるなかったら追加
	//for (auto&& list : m_UIList)
	//{
	//	if (list->GetDate().name == UIdate.name)
	//	{
	//		hit = true;
	//		list->SetDate(UIdate);
	//	}
	//}
	//if (!hit)
	//{
	//	std::shared_ptr<ImGuiUI> addUI = std::make_shared<ImGuiUI>();
	//	addUI->SetDate(UIdate);
	//	m_UIList.push_back(addUI);
	//}

	for (auto&& list : m_UIList)
	{
		if (list->GetDate().name == UIdate.name)
		{
			list->SetDate(UIdate);

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->GetName() == UIdate.name)
				{
					obj->SetPosition(UIdate.pos);
					obj->SetScale(UIdate.scale);

					std::cout << "Updated Object: " << obj->GetName()
						<< " Pos: (" << obj->GetPosition().x << ", "
						<< obj->GetPosition().y << ", " << obj->GetPosition().z << ")"
						<< " Scale: (" << obj->GetScale().x << ", "
						<< obj->GetScale().y << ", " << obj->GetScale().z << ")"
						<< std::endl;
				}
			}
		}
	}

}

Date ImGuiManager::GetTarget(const std::string name)
{
	Date Target = {};
	for (auto&& list : m_UIList)
	{
		if (list->GetDate().name == name)
		{
			Target = list->GetDate();
		}
	}

	return Target;
}

void ImGuiManager::EditObject(const std::string& name)
{
	//ImGui::Begin("Object Editor");

	//for (auto&& list : m_UIList)
	//{
	//	Date& data = list->GetDate();
	//	bool changed = false; // 値が変更されたかを検知

	//	if (ImGui::CollapsingHeader(data.name.c_str()))
	//	{
	//		// 位置編集
	//		ImGui::Text("Position");
	//		changed |= ImGui::SliderFloat(("X##" + data.name).c_str(), &data.pos.x, -100.0f, 100.0f);
	//		changed |= ImGui::SliderFloat(("Y##" + data.name).c_str(), &data.pos.y, -100.0f, 100.0f);
	//		changed |= ImGui::SliderFloat(("Z##" + data.name).c_str(), &data.pos.z, -100.0f, 100.0f);

	//		changed |= ImGui::InputFloat(("X Input##" + data.name).c_str(), &data.pos.x);
	//		changed |= ImGui::InputFloat(("Y Input##" + data.name).c_str(), &data.pos.y);
	//		changed |= ImGui::InputFloat(("Z Input##" + data.name).c_str(), &data.pos.z);

	//		// スケール編集
	//		ImGui::Text("Scale");
	//		changed |= ImGui::SliderFloat(("Scale X##" + data.name).c_str(), &data.scale.x, 0.1f, 10.0f);
	//		changed |= ImGui::SliderFloat(("Scale Y##" + data.name).c_str(), &data.scale.y, 0.1f, 10.0f);
	//		changed |= ImGui::SliderFloat(("Scale Z##" + data.name).c_str(), &data.scale.z, 0.1f, 10.0f);

	//		changed |= ImGui::InputFloat(("Scale X Input##" + data.name).c_str(), &data.scale.x);
	//		changed |= ImGui::InputFloat(("Scale Y Input##" + data.name).c_str(), &data.scale.y);
	//		changed |= ImGui::InputFloat(("Scale Z Input##" + data.name).c_str(), &data.scale.z);
	//	}

	//	// 🔥 値が変更されたらオブジェクトに即座に適用
	//	if (changed)
	//	{
	//		SetDateUI(data);
	//	}
	//}

	//ImGui::End();
}

void ImGuiManager::EditObjects()
{
	ImGui::Begin("Object Editor");

	for (auto&& list : m_UIList)
	{
		Date& data = list->GetDate();
		bool changed = false;

		if (ImGui::CollapsingHeader(data.name.c_str())) // すでに個別な名前なのでそのまま使う
		{
			KdGameObject* obj = SceneManager::Instance().GetObjectByName(data.name);
			if (!obj) continue;

			Math::Vector3 currentPos = obj->GetPosition();
			Math::Vector3 currentScale = obj->GetScale();

			ImGui::Text("Position");
			changed |= ImGui::SliderFloat(("X##" + data.name).c_str(), &data.pos.x, -100.0f, 100.0f);
			changed |= ImGui::SliderFloat(("Y##" + data.name).c_str(), &data.pos.y, -100.0f, 100.0f);
			changed |= ImGui::SliderFloat(("Z##" + data.name).c_str(), &data.pos.z, -100.0f, 100.0f);

			changed |= ImGui::InputFloat(("X Input##" + data.name).c_str(), &data.pos.x);
			changed |= ImGui::InputFloat(("Y Input##" + data.name).c_str(), &data.pos.y);
			changed |= ImGui::InputFloat(("Z Input##" + data.name).c_str(), &data.pos.z);

			ImGui::Text("Scale");
			changed |= ImGui::SliderFloat(("Scale X##" + data.name).c_str(), &data.scale.x, 0.1f, 10.0f);
			changed |= ImGui::SliderFloat(("Scale Y##" + data.name).c_str(), &data.scale.y, 0.1f, 10.0f);
			changed |= ImGui::SliderFloat(("Scale Z##" + data.name).c_str(), &data.scale.z, 0.1f, 10.0f);
		}

		if (changed)
		{
			SetDateUI(data);
		}
	}

	if (ImGui::Button("Save to JSON"))
	{
		SaveToJson();
	}

	if (ImGui::Button("Load from JSON"))
	{
		LoadFromJson();
	}

	ImGui::End();
}


void ImGuiManager::SaveToJson()
{
	for (auto&& list : m_UIList)
	{
		Date& data = list->GetDate();

		// オブジェクトの m_filePath を取得
		std::string filePath;
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->GetName() == data.name)
			{
				filePath = obj->GetFilePath();
				break;
			}
		}

		if (filePath.empty())
		{
			std::cerr << "Skipping saving for object: " << data.name << " (No file path set)" << std::endl;
			continue;
		}

		// 既存の JSON を読み込み
		nlohmann::json jsonData;
		std::ifstream inFile(filePath);
		if (inFile.is_open())
		{
			inFile >> jsonData;
			inFile.close();
		}

		// 🔥 オブジェクト名をキーにして `pos` と `scale` を保存
		jsonData[data.name]["pos"]["x"] = data.pos.x;
		jsonData[data.name]["pos"]["y"] = data.pos.y;
		jsonData[data.name]["pos"]["z"] = data.pos.z;
		jsonData[data.name]["scale"]["x"] = data.scale.x;
		jsonData[data.name]["scale"]["y"] = data.scale.y;
		jsonData[data.name]["scale"]["z"] = data.scale.z;

		// JSONファイルを書き込み
		std::ofstream outFile(filePath);
		if (outFile.is_open())
		{
			outFile << jsonData.dump(4);
			outFile.close();
			std::cout << "Saved object: " << data.name << " to " << filePath << std::endl;
		}
		else
		{
			std::cerr << "Failed to save JSON file: " << filePath << std::endl;
		}
	}
}

void ImGuiManager::LoadFromJson()
{
	for (auto&& list : m_UIList)
	{
		Date data = list->GetDate();

		// オブジェクトの m_filePath を取得
		std::string filePath;
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->GetName() == data.name)
			{
				filePath = obj->GetFilePath();
				break;
			}
		}

		if (filePath.empty())
		{
			std::cerr << "Skipping loading for object: " << data.name << " (No file path set)" << std::endl;
			continue;
		}

		// JSONファイルを読み込み
		std::ifstream file(filePath);
		if (!file.is_open())
		{
			std::cerr << "Failed to open JSON file: " << filePath << std::endl;
			continue;
		}

		nlohmann::json jsonData;
		file >> jsonData;
		file.close();

		// 🔥 オブジェクト名をキーにしてネストされたデータを取得
		if (jsonData.contains(data.name))
		{
			auto& objData = jsonData[data.name];

			if (objData.contains("pos"))
			{
				data.pos.x = objData["pos"].value("x", data.pos.x);
				data.pos.y = objData["pos"].value("y", data.pos.y);
				data.pos.z = objData["pos"].value("z", data.pos.z);
			}

			if (objData.contains("scale"))
			{
				data.scale.x = objData["scale"].value("x", data.scale.x);
				data.scale.y = objData["scale"].value("y", data.scale.y);
				data.scale.z = objData["scale"].value("z", data.scale.z);
			}
		}

		list->SetDate(data);

		// 🔥 ゲームオブジェクトに適用
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->GetName() == data.name)
			{
				obj->SetPosition(data.pos);
				obj->SetScale(data.scale);
			}
		}

		std::cout << "Loaded object: " << data.name << " from " << filePath << std::endl;
	}
}

void ImGuiManager::RegisterObjects()
{
	const auto& objList = SceneManager::Instance().GetObjList();

	// UIリストに含まれるオブジェクトをチェック
	std::unordered_set<std::string> existingNames;
	for (const auto& ui : m_UIList)
	{
		existingNames.insert(ui->GetDate().name);
	}

	for (auto& obj : objList)
	{
		std::string objName = obj->GetName();

		// 名前が設定されていないオブジェクトは追加しない
		if (objName.empty())
		{
			std::cout << "Skipped unnamed object." << std::endl;
			continue;
		}

		// すでに登録されている場合はスキップ
		if (existingNames.find(objName) != existingNames.end())
		{
			continue;
		}

		// 新規オブジェクトを登録
		Date objData;
		objData.name = obj->GetName();
		objData.pos = obj->GetPosition();
		objData.scale = obj->GetScale();

		std::shared_ptr<ImGuiUI> addUI = std::make_shared<ImGuiUI>();
		addUI->SetDate(objData);
		m_UIList.push_back(addUI);

		std::cout << "Registered Object: " << objData.name
			<< " Pos: (" << objData.pos.x << ", " << objData.pos.y << ", " << objData.pos.z << ")"
			<< " Scale: (" << objData.scale.x << ", " << objData.scale.y << ", " << objData.scale.z << ")"
			<< std::endl;
	}
}

void ImGuiUI::Update()
{
	{
		char label[128] = {};
		snprintf(label, sizeof(label), "%s", m_date.name.c_str());
		if (ImGui::TreeNode(label))
		{
			char pos[128] = {};
			snprintf(pos, sizeof(pos), "POS:%s", m_date.name.c_str());
			if (ImGui::TreeNode(pos))
			{
				m_date.pos.x = DrawSlider(m_date.pos.x, "pos.x: %s", m_date.name);
				m_date.pos.x = DrawInput(m_date.pos.x, "In:pos.x: %s", m_date.name);
				m_date.pos.y = DrawSlider(m_date.pos.y, "pos.y: %s", m_date.name);
				m_date.pos.y = DrawInput(m_date.pos.y, "In:pos.y: %s", m_date.name);
				m_date.pos.z = DrawSlider(m_date.pos.z, "pos.z: %s", m_date.name);
				m_date.pos.z = DrawInput(m_date.pos.z, "In:pos.z: %s", m_date.name);
				ImGui::TreePop();
			}
			char scale[128] = {};
			snprintf(scale, sizeof(scale), "SCALE:%s", m_date.name.c_str());
			if (ImGui::TreeNode(scale))
			{
				m_date.scale.x = DrawSlider(m_date.scale.x, "scale.x: %s", m_date.name);
				m_date.scale.x = DrawInput(m_date.scale.x, "In:scale.x: %s", m_date.name);
				m_date.scale.y = DrawSlider(m_date.scale.y, "scale.y: %s", m_date.name);
				m_date.scale.y = DrawInput(m_date.scale.y, "In:scale.y: %s", m_date.name);
				m_date.scale.z = DrawSlider(m_date.scale.z, "scale.z: %s", m_date.name);
				m_date.scale.z = DrawInput(m_date.scale.z, "In:scale.z: %s", m_date.name);
				ImGui::TreePop();
			}
			char debug[128] = {};
			snprintf(debug, sizeof(debug), "DEBUG:%s", m_date.name.c_str());
			if (ImGui::TreeNode(debug))
			{
				m_date.debug1 = DrawSlider(m_date.debug1, "debug1: %s", m_date.name);
				m_date.debug1 = DrawInput(m_date.debug1, "In:debug1: %s", m_date.name);
				m_date.debug2 = DrawSlider(m_date.debug2, "debug2: %s", m_date.name);
				m_date.debug2 = DrawInput(m_date.debug2, "In:debug2: %s", m_date.name);
				m_date.debug3 = DrawSlider(m_date.debug3, "debug3: %s", m_date.name);
				m_date.debug3 = DrawInput(m_date.debug3, "In:debug3: %s", m_date.name);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		//ImGui::EndTabBar();
	}

	//ui->SetDate(writeDate);
}

float ImGuiUI::DrawSlider(float value, const char display[128], std::string name)
{
	char posX[128] = {};
	snprintf(posX, sizeof(posX), display, name.c_str());
	ImGui::SliderFloat((const char*)posX, &value, -10000, 10000);
	return value;
}

float ImGuiUI::DrawInput(float value, const char display[128], std::string name)
{
	char posX[128] = {};
	snprintf(posX, sizeof(posX), display, name.c_str());
	ImGui::InputFloat((const char*)posX, &value, -10000, 10000);
	return value;
}
