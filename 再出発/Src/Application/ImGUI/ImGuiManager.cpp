#include "ImGuiManager.h"
#include "Application/main.h"

void ImGuiManager::Update()
{
	{
		for (auto&& list : m_UIList)
		{
			list->Update();
		}
	}
}

void ImGuiManager::SetDateUI(const Date& UIdate)
{
	bool hit = false;
	//名前で探すあったらデータを書き換えるなかったら追加
	for (auto&& list : m_UIList)
	{
		if (list->GetDate().name == UIdate.name)
		{
			hit = true;
			list->SetDate(UIdate);
		}
	}
	if (!hit)
	{
		std::shared_ptr<ImGuiUI> addUI = std::make_shared<ImGuiUI>();
		addUI->SetDate(UIdate);
		m_UIList.push_back(addUI);
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
