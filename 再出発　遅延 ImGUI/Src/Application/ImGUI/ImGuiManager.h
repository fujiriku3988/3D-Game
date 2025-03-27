#pragma once

struct Date
{
	std::string name = {};
	Math::Vector3 pos = {};
	Math::Vector3 scale = {};
	int id = {};
	float debug1 = 0;
	float debug2 = 0;
	float debug3 = 0;
	float debug4 = 0;
};

class ImGuiUI
{
public:
	ImGuiUI() {};
	~ImGuiUI() {};

	void Update();

	//Date const GetDate()const { return m_date; }
	//Date GetDate() { return m_date; }
	Date& GetDate() { return m_date; }
	void SetDate(const Date& _date) { m_date = _date; }
private:

	Date m_date;

	float DrawSlider(float value, const char display[128], std::string name);
	float DrawInput(float value, const char display[128], std::string name);
};

class ImGuiManager 
{
public:

	void Update();

	//データの名前
	Date m_date;

	//データを保存するもの
	void SetDateUI(const Date& UIdate);
	Date GetTarget(const std::string name);

	void EditObject(const std::string& name);
	void EditObjects();

	void SaveToJson();
	void LoadFromJson();

	void RegisterObjects();

private:

	std::list<std::shared_ptr<ImGuiUI>>	  m_UIList;

private:

	ImGuiManager() {};
	~ImGuiManager() {};

public:

	static ImGuiManager& Instance()
	{
		static ImGuiManager instance;
		return instance;
	}

};
