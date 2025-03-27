#include "StageScene4.h"
#include"../../SceneManager.h"

#include"../../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../../GameObject/Character/Player/Player.h"

#include"../../../GameObject/Terrains/Stage/Stage.h"
#include"../../../GameObject/Terrains/Sphere/Sphere.h"

#include"../../../GameObject/UI/Button/Play/PlayButton.h"
#include"../../../GameObject/UI/Button/Restart/RestartButton.h"
#include"../../../GameObject/UI/Button/Return/ReturnButton.h"
#include"../../../GameObject/UI/Button/KeyB/KeyB.h"
#include"../../../GameObject/UI/Button/KeyR/KeyR.h"
#include"../../../GameObject/UI/Button/KeyEnter/KeyEnter.h"
#include"../../../GameObject/UI/Frame/ButtonFrame/ButtonFrame.h"
#include"../../../GameObject/UI/BackGround/BlackBack/BlackBack.h"
#include"../../../GameObject/UI/Star/Star.h"
#include"../../../GameObject/UI/StarEmpty/StarEmpty.h"
#include"../../../GameObject/UI/GameTime/GameTime.h"
#include"../../../GameObject/UI/ClearTime/ClearTime.h"
#include"../../../GameObject/UI/ClearStar/ClearStar.h"
#include"../../../GameObject/UI/Text/StageClear/StageClearTXT.h"

#include"../../../GameObject/Object/PressurePlate/BlockPlate/BlockPlate.h"
#include"../../../GameObject/Object/PressurePlate/FencePlate/FencePlate.h"
#include"../../../GameObject/Object/Block/BlueBlock/BlueBlock.h"
#include"../../../GameObject/Object/Fence/Fence.h"
#include"../../../GameObject/Object/GoalPoint/GoalPoint.h"

void StageScene4::Event()
{
	
}

void StageScene4::Init()
{
	//ステージ切り替え時エフェクト初期化
	KdEffekseerManager::GetInstance().StopAllEffect();
	//エフェクシア用
	Math::Viewport viewPort;
	KdDirect3D::Instance().CopyViewportInfo(viewPort);
	float width = viewPort.width;
	float height = viewPort.height;
	KdEffekseerManager::GetInstance().Create((float)width, (float)height);

	//=================ステージ全体=================//
	//スカイボックス
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->Init("Asset/Data/Json/Sphere/Sphere.json");
	AddObject(sphere);

	//ステージ本体
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	stage->Init("Asset/Data/Json/Stage/Stage4/Stage4.json","Stage4");
	AddObject(stage);

	//ゴール
	int goalID = 1;
	std::shared_ptr<GoalPoint> goalPoint = std::make_shared<GoalPoint>();
	goalPoint->Init("Asset/Data/Json/Stage/Stage4/GoalPoint/GoalPoint.json", goalID++);
	AddObject(goalPoint);

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init("Asset/Data/Json/Player/Stage4/Player.json");
	AddObject(player);

	//=================ブロック=================//

	int blockID = 1;

	std::shared_ptr<BlueBlock> blueBlock1 = std::make_shared<BlueBlock>();
	blueBlock1->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock1.json", blockID++);
	AddObject(blueBlock1);

	std::shared_ptr<BlueBlock> blueBlock2 = std::make_shared<BlueBlock>();
	blueBlock2->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock2.json", blockID++);
	AddObject(blueBlock2);

	std::shared_ptr<BlueBlock> blueBlock3 = std::make_shared<BlueBlock>();
	blueBlock3->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock3.json", blockID++);
	AddObject(blueBlock3);

	std::shared_ptr<BlueBlock> blueBlock4 = std::make_shared<BlueBlock>();
	blueBlock4->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock4.json", blockID++);
	AddObject(blueBlock4);

	std::shared_ptr<BlueBlock> blueBlock5 = std::make_shared<BlueBlock>();
	blueBlock5->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock5.json", blockID++);
	AddObject(blueBlock5);

	std::shared_ptr<BlueBlock> blueBlock6 = std::make_shared<BlueBlock>();
	blueBlock6->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock6.json", blockID++);
	AddObject(blueBlock6);

	std::shared_ptr<BlueBlock> blueBlock7 = std::make_shared<BlueBlock>();
	blueBlock7->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock7.json", blockID++);
	AddObject(blueBlock7);

	std::shared_ptr<BlueBlock> blueBlock8 = std::make_shared<BlueBlock>();
	blueBlock8->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock8.json", blockID++);
	AddObject(blueBlock8);

	std::shared_ptr<BlueBlock> blueBlock9 = std::make_shared<BlueBlock>();
	blueBlock9->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock9.json", blockID++);
	AddObject(blueBlock9);

	std::shared_ptr<BlueBlock> blueBlock10 = std::make_shared<BlueBlock>();
	blueBlock10->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock10.json", blockID++);
	AddObject(blueBlock10);

	std::shared_ptr<BlueBlock> blueBlock11 = std::make_shared<BlueBlock>();
	blueBlock11->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock11.json", blockID++);
	AddObject(blueBlock11);

	std::shared_ptr<BlueBlock> blueBlock12 = std::make_shared<BlueBlock>();
	blueBlock12->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock12.json", blockID++);
	AddObject(blueBlock12);

	std::shared_ptr<BlueBlock> blueBlock13 = std::make_shared<BlueBlock>();
	blueBlock13->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock13.json", blockID++);
	AddObject(blueBlock13);

	std::shared_ptr<BlueBlock> blueBlock14 = std::make_shared<BlueBlock>();
	blueBlock14->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock14.json", blockID++);
	AddObject(blueBlock14);

	std::shared_ptr<BlueBlock> blueBlock15 = std::make_shared<BlueBlock>();
	blueBlock15->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock15.json", blockID++);
	AddObject(blueBlock15);

	std::shared_ptr<BlueBlock> blueBlock16 = std::make_shared<BlueBlock>();
	blueBlock16->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock16.json", blockID++);
	AddObject(blueBlock16);

	std::shared_ptr<BlueBlock> blueBlock17 = std::make_shared<BlueBlock>();
	blueBlock17->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock17.json", blockID++);
	AddObject(blueBlock17);

	std::shared_ptr<BlueBlock> blueBlock18 = std::make_shared<BlueBlock>();
	blueBlock18->Init("Asset/Data/Json/Stage/Stage4/BlueBlock/BlueBlock18.json", blockID++);
	AddObject(blueBlock18);
	//=================ブロック=================//

	//フェンス
	int fenceID = 1;
	std::shared_ptr<Fence> fence1 = std::make_shared<Fence>();
	fence1->Init("Asset/Data/Json/Stage/Stage4/Fence/Fence1.json", fenceID++);
	AddObject(fence1);

	std::shared_ptr<Fence> fence2 = std::make_shared<Fence>();
	fence2->Init("Asset/Data/Json/Stage/Stage4/Fence/Fence2.json", fenceID++);
	AddObject(fence2);

	//=================感圧式スイッチ=================//
	int blockPlateID = 1;
	std::shared_ptr<BlockPlate> blockPlate1 = std::make_shared<BlockPlate>();
	blockPlate1->Init("Asset/Data/Json/Stage/Stage4/PressurePlate/BlockPlate/BlockPlate1.json", blockPlateID++);
	//ブロックの情報を渡す
	blockPlate1->AddBlueBlock(blueBlock1);
	blockPlate1->AddBlueBlock(blueBlock2);
	blockPlate1->AddBlueBlock(blueBlock3);
	blockPlate1->AddBlueBlock(blueBlock4);
	blockPlate1->AddBlueBlock(blueBlock5);
	blockPlate1->AddBlueBlock(blueBlock6);
	blockPlate1->AddBlueBlock(blueBlock7);
	blockPlate1->AddBlueBlock(blueBlock8);
	blockPlate1->AddBlueBlock(blueBlock9);
	blockPlate1->AddBlueBlock(blueBlock10);
	blockPlate1->AddBlueBlock(blueBlock11);
	blockPlate1->AddBlueBlock(blueBlock12);
	blockPlate1->AddBlueBlock(blueBlock13);
	blockPlate1->AddBlueBlock(blueBlock14);
	blockPlate1->AddBlueBlock(blueBlock15);
	blockPlate1->AddBlueBlock(blueBlock16);
	blockPlate1->AddBlueBlock(blueBlock17);
	blockPlate1->AddBlueBlock(blueBlock18);
	AddObject(blockPlate1);

	int fencePlateID = 1;
	std::shared_ptr<FencePlate> fencePlate1 = std::make_shared<FencePlate>();
	fencePlate1->Init("Asset/Data/Json/Stage/Stage4/PressurePlate/FencePlate/FencePlate1.json", fencePlateID++);
	fencePlate1->AddFence(fence1);
	fencePlate1->AddFence(fence2);
	AddObject(fencePlate1);

	std::shared_ptr<FencePlate> fencePlate2 = std::make_shared<FencePlate>();
	fencePlate2->Init("Asset/Data/Json/Stage/Stage4/PressurePlate/FencePlate/FencePlate2.json", fencePlateID++);
	fencePlate2->AddFence(fence1);
	fencePlate2->AddFence(fence2);
	AddObject(fencePlate2);

	//=================感圧式スイッチ1=================//

	//==================================================//

	//クリア後の背景色落とす用
	std::shared_ptr<BlackBack> blackBack = std::make_shared<BlackBack>();
	blackBack->Init("Asset/Data/Json/UI/Back/BlackBack.json");
	AddObject(blackBack);

	//時間表示
	std::shared_ptr<GameTime> gameTime = std::make_shared<GameTime>();
	gameTime->Init("Asset/Data/Json/UI/GameTime/GameTime.json");
	AddObject(gameTime);

	//=================クリアランクの星表示=================//
	//クリア時間にあった星での評価
	std::shared_ptr<StarEmpty> starEmp = std::make_shared<StarEmpty>();
	starEmp->Init("Asset/Data/Json/UI/StarEmpty/StarEmpty.json");
	AddObject(starEmp);

	std::shared_ptr<Star> star1 = std::make_shared<Star>();
	star1->Init("Asset/Data/Json/UI/Star/Stage4/Star1.json");
	AddObject(star1);

	std::shared_ptr<Star> star2 = std::make_shared<Star>();
	star2->Init("Asset/Data/Json/UI/Star/Stage4/Star2.json");
	AddObject(star2);

	std::shared_ptr<Star> star3 = std::make_shared<Star>();
	star3->Init("Asset/Data/Json/UI/Star/Stage4/Star3.json");
	AddObject(star3);
	//==================================================//

	//==============クリアランクレベル表示=================//
	//どの程度の時間でクリアすれば良いかの指標
	std::shared_ptr<ClearTime> clearTime1 = std::make_shared<ClearTime>();
	clearTime1->Init("Asset/Data/Json/UI/ClearTime/Stage4/ClearTime1.json");
	AddObject(clearTime1);

	std::shared_ptr<ClearTime> clearTime2 = std::make_shared<ClearTime>();
	clearTime2->Init("Asset/Data/Json/UI/ClearTime/Stage4/ClearTime2.json");
	AddObject(clearTime2);

	std::shared_ptr<ClearTime> clearTime3 = std::make_shared<ClearTime>();
	clearTime3->Init("Asset/Data/Json/UI/ClearTime/Stage4/ClearTime3.json");
	AddObject(clearTime3);

	std::shared_ptr<ClearStar> clearStar1 = std::make_shared<ClearStar>();
	clearStar1->Init("Asset/Data/Json/UI/ClearStar/GameScene/ClearStar1.json");
	AddObject(clearStar1);

	std::shared_ptr<ClearStar> clearStar2 = std::make_shared<ClearStar>();
	clearStar2->Init("Asset/Data/Json/UI/ClearStar/GameScene/ClearStar2.json");
	AddObject(clearStar2);

	std::shared_ptr<ClearStar> clearStar3 = std::make_shared<ClearStar>();
	clearStar3->Init("Asset/Data/Json/UI/ClearStar/GameScene/ClearStar3.json");
	AddObject(clearStar3);
	
	//==================================================//

	//ステージクリアのテキスト表示
	std::shared_ptr<StageClearTXT> stageClearTXT = std::make_shared<StageClearTXT>();
	stageClearTXT->Init("Asset/Data/Json/UI/Text/StageClearTXT.json");
	AddObject(stageClearTXT);

	//==================================================//
	//クリア後のUI
	std::shared_ptr<ButtonFrame> bFrame = std::make_shared<ButtonFrame>();
	bFrame->Init("Asset/Data/Json/UI/Frame/ButtonFrame.json");
	AddObject(bFrame);

	std::shared_ptr<PlayButton> bPlay = std::make_shared<PlayButton>();
	bPlay->Init("Asset/Data/Json/UI/Button/Play.json");
	AddObject(bPlay);

	std::shared_ptr<RestartButton> bRestart = std::make_shared<RestartButton>();
	bRestart->Init("Asset/Data/Json/UI/Button/Restart.json");
	AddObject(bRestart);

	std::shared_ptr<ReturnButton> bReturn = std::make_shared<ReturnButton>();
	bReturn->Init("Asset/Data/Json/UI/Button/Return.json");
	AddObject(bReturn);

	std::shared_ptr<KeyR> keyR = std::make_shared<KeyR>();
	keyR->Init("Asset/Data/Json/UI/Button/KeyR.json");
	AddObject(keyR);

	std::shared_ptr<KeyB> keyB = std::make_shared<KeyB>();
	keyB->Init("Asset/Data/Json/UI/Button/KeyB.json");
	AddObject(keyB);

	std::shared_ptr<KeyEnter> keyEnter = std::make_shared<KeyEnter>();
	keyEnter->Init("Asset/Data/Json/UI/Button/KeyEnter.json");
	AddObject(keyEnter);
	//==================================================//

	//カメラ
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init("Asset/Data/Json/Camera/TPSCamera/TPSCamera.json");
	camera->SetTarget(player);
	AddObject(camera);

	//セットする系
	player->SetCamera(camera);
	player->SetGameTime(gameTime);
	star1->SetGameTime(gameTime);
	star2->SetGameTime(gameTime);
	star3->SetGameTime(gameTime);
	goalPoint->SetCamera(camera);
	goalPoint->SetPlayer(player);
	goalPoint->SetGameTime(gameTime);
	goalPoint->AddUI(bFrame);
	goalPoint->AddUI(bPlay);
	goalPoint->AddUI(bRestart);
	goalPoint->AddUI(bReturn);
	goalPoint->AddUI(blackBack);
	goalPoint->AddUI(keyR);
	goalPoint->AddUI(keyB);
	goalPoint->AddUI(keyEnter);
	goalPoint->AddUI(star1);
	goalPoint->AddUI(star2);
	goalPoint->AddUI(star3);
	goalPoint->AddUI(starEmp);
	goalPoint->AddUI(gameTime);
	goalPoint->AddUI(clearTime1);
	goalPoint->AddUI(clearTime2);
	goalPoint->AddUI(clearTime3);
	goalPoint->AddUI(clearStar1);
	goalPoint->AddUI(clearStar2);
	goalPoint->AddUI(clearStar3);
	goalPoint->AddUI(stageClearTXT);

	KdEffekseerManager::GetInstance().SetCamera(camera->GetCamera());
}
