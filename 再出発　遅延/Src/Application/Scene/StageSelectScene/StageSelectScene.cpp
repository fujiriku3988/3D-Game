#include "StageSelectScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/Text/Title/TitleTXT.h"
#include"../../GameObject/UI/Text/StageSelect/StageSelectTXT.h"
#include"../../GameObject/UI/Text/NumOne/NumOne.h"
#include"../../GameObject/UI/Text/NumTwo/NumTwo.h"

#include"../../GameObject/UI/Frame/StageFrame/StageFrame.h"

#include"../../GameObject/UI/BackGround/TitleBack/TitleBack.h"

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

	//=======================================================================//
	//ステージ１用
	std::shared_ptr<StageFrame> stageFrame1 = std::make_shared<StageFrame>();
	stageFrame1->Init("Asset/Data/Json/UI/Frame/StageFrame/StageFrame1/StageFrame1.json");
	AddObject(stageFrame1);

	std::shared_ptr<NumOne> numOne = std::make_shared<NumOne>();
	numOne->Init("Asset/Data/Json/UI/Text/Number/NumOne/NumOne.json");
	AddObject(numOne);
	//=======================================================================//

	//=======================================================================//
	//ステージ２用
	std::shared_ptr<StageFrame> stageFrame2 = std::make_shared<StageFrame>();
	stageFrame2->Init("Asset/Data/Json/UI/Frame/StageFrame/StageFrame2/StageFrame2.json");
	AddObject(stageFrame2);

	std::shared_ptr<NumTwo> numTwo = std::make_shared<NumTwo>();
	numTwo->Init("Asset/Data/Json/UI/Text/Number/NumTwo/NumTwo.json");
	AddObject(numTwo);
	//=======================================================================//

}

