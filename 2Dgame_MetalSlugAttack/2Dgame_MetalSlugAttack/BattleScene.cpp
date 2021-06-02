#include "BattleScene.h"
#include "Image.h"
#include "CollisionChecker.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
HRESULT BattleScene::Init()
{
	apImageCount = 0.0f;
	attackUndoFrame = 14;
	attackReadyFrame = 3;
	attackFireFrame = 10;
	checkAttackCool = 0.0f;
	apPurchaseFrame = 14;
	changeTime = 0.0f;
	currFrameX = 0;
	attackCool = 5.0f;
	attackStatus = ATTACKSTATUS::UNDO;
	startTimer = 0.0f;
	failedTimer = 0.0f;
	winTimer = 0.0f;
	textMoveTimer = 0;
	textPosition[0] = 0;
	textPosition[1] = WINSIZE_X;
	//UiImage Add
	ImageManager::GetSingleton()->AddImage("background", "Image/Background/background.bmp", WINSIZE_X, 380);
	ImageManager::GetSingleton()->AddImage("ui_up", "Image/Ui/Ui_Up.bmp", WINSIZE_X, 70);
	ImageManager::GetSingleton()->AddImage("ui_down", "Image/Ui/Ui_Down.bmp", WINSIZE_X, 150);
	ImageManager::GetSingleton()->AddImage("attack_undo", "Image/Ui/attack_undo.bmp", 735, 49, 15, 1, true, RGB(128, 128, 192));
	ImageManager::GetSingleton()->AddImage("attack_ready", "Image/Ui/attack_ready.bmp", 212, 49, 4, 1, true, RGB(128, 128, 192));
	ImageManager::GetSingleton()->AddImage("attack_fire", "Image/Ui/attack_fire.bmp", 583, 49, 11, 1, true, RGB(128, 128, 192));
	ImageManager::GetSingleton()->AddImage("player_hpframe", "Image/Ui/Player_HpFrame.bmp", 240, 50, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("enemy_hpframe", "Image/Ui/Enemy_HpFrame.bmp", 240, 50, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("player", "Image/Ui/Player.bmp", 60, 30, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("enemy", "Image/Ui/Enemy.bmp", 60, 30, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("minimap", "Image/Ui/minimap.bmp", 270, 50, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("enemyhp", "Image/Ui/Red_Bar.bmp", 178, 8, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("playerhp", "Image/Ui/Yellow_Bar.bmp", 178, 8, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("apbar", "Image/Ui/Pointbar.bmp", 200, 76, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("mission", "Image/Ui/mission.bmp", 420, 80, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("start", "Image/Ui/start.bmp", 420, 80, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("complete", "Image/Ui/complete.bmp", 500, 80, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("failedMission", "Image/Ui/failmission.bmp", 500, 80, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("failed", "Image/Ui/failed.bmp", 500, 80, true, RGB(255, 0, 255));
	//Character_Eri Image Add
	ImageManager::GetSingleton()->AddImage("Eri_walk", "Image/Eri/Eri_walk.bmp", 960, 50, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_stand", "Image/Eri/Eri_stand.bmp", 640, 50, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_fire", "Image/Eri/Eri_fire.bmp", 480, 50, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_win", "Image/Eri/Eri_win.bmp", 560, 50, 7, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_dead", "Image/Eri/Eri_dead.bmp", 1680, 50, 21, 1, true, RGB(255, 255, 255));
	//Character_Trevor Image Add
	ImageManager::GetSingleton()->AddImage("Trevor_walk", "Image/Trevor/trevor_walk.bmp", 880, 80, 11, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Trevor_stand", "Image/Trevor/trevor_stand.bmp", 640, 80, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Trevor_fire", "Image/Trevor/trevor_fire.bmp", 560, 80, 7, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Trevor_dead", "Image/Trevor/trevor_dead.bmp", 1440, 80, 18, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Trevor_win", "Image/Trevor/trevor_win.bmp", 1200, 80, 15, 1, true, RGB(255, 255, 255));
	//Character_Amber Image Add
	ImageManager::GetSingleton()->AddImage("Amber_walk", "Image/Amber/amber_walk.bmp", 2880, 80, 16, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Amber_stand", "Image/Amber/amber_stand.bmp", 1260, 80, 7, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Amber_fire", "Image/Amber/amber_fire.bmp", 3060, 80, 17, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Amber_dead", "Image/Amber/amber_dead.bmp", 1800, 80, 10, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Amber_win", "Image/Amber/amber_win.bmp", 5940, 80, 33, 1, true, RGB(255, 255, 255));
	//Character_Ralf Image Add
	ImageManager::GetSingleton()->AddImage("Ralf_walk", "Image/Ralf/ralf_walk.bmp", 960, 80, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Ralf_stand", "Image/Ralf/ralf_stand.bmp", 480, 80, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Ralf_fire", "Image/Ralf/ralf_fire.bmp", 1280, 80, 16, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Ralf_dead", "Image/Ralf/ralf_dead.bmp", 1520, 80, 19, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Ralf_win", "Image/Ralf/ralf_win.bmp", 1200, 80, 15, 1, true, RGB(255, 255, 255));
	//Character_Marco Image Add
	ImageManager::GetSingleton()->AddImage("Marco_walk", "Image/Marco/marco_walk.bmp", 960, 80, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Marco_stand", "Image/Marco/marco_stand.bmp", 480, 80, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Marco_fire", "Image/Marco/marco_fire.bmp", 640, 80, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Marco_dead", "Image/Marco/marco_dead.bmp", 1520, 80, 19, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Marco_win", "Image/Marco/marco_win.bmp", 480, 80, 6, 1, true, RGB(255, 255, 255));
	//Rifle Image Add
	ImageManager::GetSingleton()->AddImage("rifle_stand", "Image/Rifle/rifle_stand.bmp", 480, 60, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_walk", "Image/Rifle/rifle_walk.bmp", 720, 60, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_dead", "Image/Rifle/rifle_dead.bmp", 660, 60, 11, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_fire", "Image/Rifle/rifle_fire.bmp", 480, 60, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_win", "Image/Rifle/rifle_win.bmp", 360, 60, 6, 1, true, RGB(255, 255, 255));

	//Shield Image Add
	ImageManager::GetSingleton()->AddImage("shield_stand", "Image/Shield/shield_stand.bmp", 480, 80, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("shield_walk", "Image/Shield/shield_walk.bmp", 720, 80, 9, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("shield_attack", "Image/Shield/shield_attack.bmp", 1280, 80, 16, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("shield_dead", "Image/Shield/shield_dead.bmp", 960, 80, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("shield_win", "Image/Shield/shield_win.bmp", 320, 80, 4, 1, true, RGB(255, 255, 255));

	//Allen Image Add
	ImageManager::GetSingleton()->AddImage("allen_stand", "Image/Allen/Allen_stand.bmp", 1960, 75, 14, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("allen_walk", "Image/Allen/Allen_walk.bmp", 1400, 75, 10, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("allen_fire", "Image/Allen/Allen_fire.bmp", 1260, 75, 9, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("allen_dead", "Image/Allen/Allen_dead.bmp", 1960, 75, 14, 1, true, RGB(255, 255, 255));

	text_Mission = ImageManager::GetSingleton()->FindImage("mission");
	text_Start = ImageManager::GetSingleton()->FindImage("start");
	text_Complete = ImageManager::GetSingleton()->FindImage("complete");
	failed_Mission = ImageManager::GetSingleton()->FindImage("failedMission");
	text_Failed = ImageManager::GetSingleton()->FindImage("failed");
	backGround = ImageManager::GetSingleton()->FindImage("background");
	ui_Up = ImageManager::GetSingleton()->FindImage("ui_up");
	ui_Down = ImageManager::GetSingleton()->FindImage("ui_down");

	attack_Undo = ImageManager::GetSingleton()->FindImage("attack_undo");
	attack_Ready = ImageManager::GetSingleton()->FindImage("attack_ready");
	attack_Fire = ImageManager::GetSingleton()->FindImage("attack_fire");
	hp_Frame[0] = ImageManager::GetSingleton()->FindImage("player_hpframe");
	hp_Frame[1] = ImageManager::GetSingleton()->FindImage("enemy_hpframe");
	miniMap = ImageManager::GetSingleton()->FindImage("minimap");
	pfText[0] = ImageManager::GetSingleton()->FindImage("player");
	pfText[1] = ImageManager::GetSingleton()->FindImage("enemy");
	apBar = ImageManager::GetSingleton()->FindImage("apbar");
	apWalk = ImageManager::GetSingleton()->FindImage("apwalk");
	apPurchase = ImageManager::GetSingleton()->FindImage("appurchase");

	playerMgr = new PlayerManager();
	playerMgr->BaseInit();
	enemyMgr = new EnemyManager();
	enemyMgr->BaseInit();
	collisionChecker = new CollisionChecker();
	collisionChecker->Init();
	uiMgr = new UiManager();
	uiMgr->Init();
	isEndGame = false;
	isReadyGame = false;
	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(playerMgr);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(collisionChecker);
	SAFE_RELEASE(uiMgr);
}

void BattleScene::Update()
{
	if (!isReadyGame)
	{
		StartTextMove();
	}
	if (isReadyGame)
	{
		if (!isEndGame)
		{
			uiMgr->Update();
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				uiMgr->PurchaseAp();
				if (uiMgr->CheckUnitPurchase())
				{
					int unitNum = 0;
					unitNum = uiMgr->PurchaseUnit();
					playerMgr->Init(unitNum, collisionChecker);
				}
			}
			EnemyInit();
		}
		playerMgr->Update();
		enemyMgr->Update();
		collisionChecker->CheckPlayer();
		collisionChecker->CheckEnemy();
		collisionChecker->CheckAlive();
		isPlayerWin = collisionChecker->CheckPlayerWin();
		isPlayerDefeat = collisionChecker->CheckPlayerDefeat();
		//Attack버튼 관련
		changeTime += TimerManager::GetSingleton()->GetElapsedTime();
		if (attackStatus == ATTACKSTATUS::UNDO)
		{
			checkAttackCool += TimerManager::GetSingleton()->GetElapsedTime();
			if (checkAttackCool >= attackCool)
			{
				attackStatus = ATTACKSTATUS::READY;
				currFrameX = 0;
				checkAttackCool = 0.0f;
			}
		}
		if (changeTime >= 0.1f)
		{
			changeTime = 0.0f;
			currFrameX++;
			if (attackStatus == ATTACKSTATUS::UNDO && currFrameX >= attackUndoFrame)
			{
				currFrameX = 0;
			}
			if (attackStatus == ATTACKSTATUS::READY && currFrameX >= attackReadyFrame)
			{
				currFrameX = 0;
			}
			if (attackStatus == ATTACKSTATUS::FIRED && currFrameX >= attackFireFrame)
			{
				currFrameX = 0;
				attackStatus = ATTACKSTATUS::UNDO;
			}
		}
		isEndGame = collisionChecker->CheckBaseHp();
		if (collisionChecker->GetEnemyBaseHp() <= 0.0f)
		{
			enemyMgr->SetIsDefeat(true);
		}
		else if (collisionChecker->GetPlayerBaseHp() <= 0.0f)
		{
			playerMgr->SetIsDefeat(true);
		}
	}
	if (isPlayerWin || isPlayerDefeat)
	{
		EndTextMove();
	}
}

void BattleScene::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 70);
	ui_Up->Render(hdc);
	ui_Down->Render(hdc, 0, 450);
	pfText[0]->Render(hdc, 20, 20);
	pfText[1]->Render(hdc, WINSIZE_X - 70, 20);
	hp_Frame[0]->Render(hdc, 100, 10);
	hp_Frame[1]->Render(hdc, WINSIZE_X - 340, 10);
	apBar->Render(hdc, 0, 400);
	uiMgr->Render(hdc);
	collisionChecker->Render(hdc);
	playerMgr->Render(hdc);
	enemyMgr->Render(hdc);
	if (attackStatus == ATTACKSTATUS::UNDO)
	{
		attack_Undo->FrameRender(hdc, 860, 470, currFrameX, 0, false, 2);
	}
	else if (attackStatus == ATTACKSTATUS::READY)
	{
		attack_Ready->FrameRender(hdc, 860, 470, currFrameX, 0, false, 2);
	}
	else if (attackStatus == ATTACKSTATUS::FIRED)
	{
		attack_Fire->FrameRender(hdc, 860, 470, currFrameX, 0, false, 2);
	}
	miniMap->Render(hdc, WINSIZE_X / 2 - 130, 10);
	if (!isReadyGame)
	{
		text_Mission->Render(hdc, textPosition[0], (WINSIZE_Y / 2) - 50);
		text_Start->Render(hdc, textPosition[1], (WINSIZE_Y / 2) + 50);
	}
	if (isPlayerWin)
	{
		text_Mission->Render(hdc, (WINSIZE_X / 2) - 150, textPosition[0]);
		text_Complete->Render(hdc, (WINSIZE_X / 2) - 180, textPosition[1]);
	}
	else if (isPlayerDefeat)
	{
		failed_Mission->Render(hdc, (WINSIZE_X / 2) - 200, textPosition[0]);
		text_Failed->Render(hdc, (WINSIZE_X / 2) - 225, textPosition[1]);
	}
}

void BattleScene::EnemyInit() //Enemy Init 작동방식 구현
{
	if (!isEndGame)
	{
		if (uiMgr->CheckEnemyAP())
		{
			int unitNum = uiMgr->GetEnemyUnitNum();
			enemyMgr->Init(unitNum, collisionChecker);
		}
	}
}

void BattleScene::StartTextMove()
{
	startTimer += TimerManager::GetSingleton()->GetElapsedTime();
	if (textPosition[0] < WINSIZE_X / 2 - 200 && textMoveTimer < 1)
	{
		startTimer = 0.0f;
		textPosition[0]++;
	}
	if (textPosition[1] > WINSIZE_X / 2 - 200 && textMoveTimer < 1)
	{
		startTimer = 0.0f;
		textPosition[1]--;
	}
	if (textPosition[0] == WINSIZE_X / 2 - 200 && textPosition[1] == WINSIZE_X / 2 - 200 && startTimer >= 1.0f)
	{
		startTimer = 0.0f;
		textMoveTimer++;
	}
	if (textMoveTimer >= 1)
	{
		textPosition[0]++;
		textPosition[1]--;
		if (textPosition[0] >= WINSIZE_X && textPosition[1] <= 0)
		{
			textPosition[0] = 0;
			textPosition[1] = WINSIZE_Y;
			textMoveTimer = 0;
			startTimer = 0.0f;
			isReadyGame = true;
		}
	}
}

void BattleScene::EndTextMove()
{
	if (isPlayerDefeat || isPlayerWin)
	{
		startTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if ((textPosition[0] <= (WINSIZE_Y / 2) - 100 && textPosition[1] >= (WINSIZE_Y / 2) - 20) && startTimer >= 0.007 )
		{
			startTimer = 0;
			textPosition[0]++;
			textPosition[1]--;
		}
		else
		{
			if (startTimer >= 1)
			{
				startTimer = 0.0f;
				textMoveTimer++;
			}
			if (textMoveTimer >= 5)
			{
				isPlayerWin = false;
				isPlayerDefeat = false;
				SceneManager::GetSingleton()->ChangeScene("IntroScene", "LoadingScene");
			}
		}
	}
}
