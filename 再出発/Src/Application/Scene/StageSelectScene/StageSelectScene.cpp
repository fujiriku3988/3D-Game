#include "StageSelectScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/Text/Title/TitleTXT.h"
#include"../../GameObject/UI/Text/StageSelect/StageSelectTXT.h"
#include"../../GameObject/UI/Frame/StageFrame/StageFrame.h"
#include"../../GameObject/UI/Text/NumOne/NumOne.h"

#include"../../GameObject/UI/Back/TitleBack/TitleBack.h"
#include"../../GameObject/UI/Frame/TextFrame/TextFrame.h"

void StageSelectScene::Event()
{
}

void StageSelectScene::Init()
{
	std::shared_ptr<TitleBack> titleBack = std::make_shared<TitleBack>();
	titleBack->Init("Asset/Data/Json/UI/Back/TitleBack.json");
	AddObject(titleBack);

	std::shared_ptr<StageSelectTXT> stageSelectTXT = std::make_shared<StageSelectTXT>();
	stageSelectTXT->Init("Asset/Data/Json/UI/Text/StageSelectTXT.json");
	AddObject(stageSelectTXT);

	std::shared_ptr<StageFrame> stageFrame = std::make_shared<StageFrame>();
	stageFrame->Init("Asset/Data/Json/UI/Frame/StageFrame.json");
	AddObject(stageFrame);

	std::shared_ptr<NumOne> numOne = std::make_shared<NumOne>();
	numOne->Init("Asset/Data/Json/UI/Text/NumOne.json");
	AddObject(numOne);
}

