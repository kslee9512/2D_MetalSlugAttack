#include "BattleScene.h"
#include "Image.h"
#include "CollisionChecker.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

HRESULT BattleScene::Init()
{
	attackUndoFrame = 14;
	attackReadyFrame = 3;
	attackFireFrame = 10;
	checkAttackCool = 0.0f;
	changeTime = 0.0f;
	currFrameX = 0;
	attackCool = 5.0f;
	attackStatus = ATTACKSTATUS::UNDO;
	playerApTimer = 0.0f;
	enemyApTimer = 0.0f;
	playerApLevel = 0;
	enemyApLevel = 0;
	playerAP = 0;
	enemyAP = 0;
	maxApLevel = 4;
	for (int i = 0; i < 5; i++)
	{
		float timer = 0.5f;
		apChargeTime[i] = timer;
		timer -= 0.1f;
	}
	for (int i = 0; i < 5; i++)
	{
		int maxInt = 3000;
		maxAp[i] = maxInt;
		maxInt += 1500;
	}
	//UiImage Add
	ImageManager::GetSingleton()->AddImage("background", "Image/Background/background.bmp", WINSIZE_X, 380);
	ImageManager::GetSingleton()->AddImage("ui_up", "Image/Ui/Ui_Up.bmp", WINSIZE_X, 70);
	ImageManager::GetSingleton()->AddImage("ui_down", "Image/Ui/Ui_Down.bmp", WINSIZE_X, 150);
	ImageManager::GetSingleton()->AddImage("unit_frame", "Image/Ui/unit_Frame.bmp", 80, 80);
	ImageManager::GetSingleton()->AddImage("unit_frame_undo", "Image/Ui/unit_Frame_undo.bmp", 80, 80);
	ImageManager::GetSingleton()->AddImage("attack_undo", "Image/Ui/attack_undo.bmp", 735, 49, 15, 1, true, RGB(128, 128, 192));
	ImageManager::GetSingleton()->AddImage("attack_ready", "Image/Ui/attack_ready.bmp", 212, 49, 4, 1, true, RGB(128, 128, 192));
	ImageManager::GetSingleton()->AddImage("attack_fire", "Image/Ui/attack_fire.bmp", 583, 49, 11, 1, true, RGB(128, 128, 192));
	ImageManager::GetSingleton()->AddImage("player_hpframe", "Image/Ui/Player_HpFrame.bmp", 240, 50, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("enemy_hpframe", "Image/Ui/Enemy_HpFrame.bmp", 240, 50, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("player", "Image/Ui/Player.bmp", 60, 30, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("enemy", "Image/Ui/Enemy.bmp", 60, 30, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("minimap", "Image/Ui/minimap.bmp", 270, 50, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("enemyhp", "Image/Ui/Red_Bar.bmp", 178, 8, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("playerhp", "Image/Ui/Yellow_Bar.bmp", 178, 8, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("apbar", "Image/Ui/Pointbar.bmp", 200, 76, true, RGB(255, 255, 255));
	//Character_Eri Image Add
	ImageManager::GetSingleton()->AddImage("Eri_walk", "Image/Eri/Eri_walk.bmp", 960, 50, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_stand", "Image/Eri/Eri_stand.bmp", 640, 50, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_fire", "Image/Eri/Eri_fire.bmp", 480, 50, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_win", "Image/Eri/Eri_win.bmp", 560, 50, 7, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_dead", "Image/Eri/Eri_dead.bmp", 1680, 50, 21, 1, true, RGB(255, 255, 255));


	//Rifle Image Add
	ImageManager::GetSingleton()->AddImage("rifle_stand", "Image/Rifle/rifle_stand.bmp", 480, 60, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_walk", "Image/Rifle/rifle_walk.bmp", 720, 60, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_dead", "Image/Rifle/rifle_dead.bmp", 660, 60, 11, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_fire", "Image/Rifle/rifle_fire.bmp", 480, 60, 8, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("rifle_win", "Image/Rifle/rifle_win.bmp", 360, 60, 6, 1, true, RGB(255, 255, 255));

	unit_Frame[0].canPurchase = true;
	unit_Frame[0].selectNum = 1;
	backGround = ImageManager::GetSingleton()->FindImage("background");
	ui_Up = ImageManager::GetSingleton()->FindImage("ui_up");
	ui_Down = ImageManager::GetSingleton()->FindImage("ui_down");
	unit_Frame[0].unit_Frame_able = ImageManager::GetSingleton()->FindImage("unit_frame");
	unit_Frame[0].unit_Frame_unable = ImageManager::GetSingleton()->FindImage("unit_frame_undo");
	attack_Undo = ImageManager::GetSingleton()->FindImage("attack_undo");
	attack_Ready = ImageManager::GetSingleton()->FindImage("attack_ready");
	attack_Fire = ImageManager::GetSingleton()->FindImage("attack_fire");
	hp_Frame[0] = ImageManager::GetSingleton()->FindImage("player_hpframe");
	hp_Frame[1] = ImageManager::GetSingleton()->FindImage("enemy_hpframe");
	miniMap = ImageManager::GetSingleton()->FindImage("minimap");
	pfText[0] = ImageManager::GetSingleton()->FindImage("player");
	pfText[1] = ImageManager::GetSingleton()->FindImage("enemy");
	player_Hpbar = ImageManager::GetSingleton()->FindImage("playerhp");
	enemy_Hpbar = ImageManager::GetSingleton()->FindImage("enemyhp");
	apBar = ImageManager::GetSingleton()->FindImage("apbar");
	unit_Frame[0].frameBox = { 250, 450, 330, 530 };
	attackBox = { 860, 470, 958, 568 };

	playerMgr = new PlayerManager();
	enemyMgr = new EnemyManager();
	collisionChecker = new CollisionChecker();

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(playerMgr);
	SAFE_RELEASE(enemyMgr);
}

void BattleScene::Update()
{
	CheckUi();
	playerMgr->Update();
	EnemyInit();
	enemyMgr->Update();
	collisionChecker->CheckEnemy();
	collisionChecker->CheckAlive();
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
	if (unit_Frame[0].canPurchase == true)
	{
		unit_Frame[0].unit_Frame_able->Render(hdc, 250, 480);
	}
	else if (unit_Frame[0].canPurchase == false)
	{
		unit_Frame[0].unit_Frame_unable->Render(hdc, 250, 480);
	}
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
	player_Hpbar->Render(hdc, 130, 30);
	enemy_Hpbar->Render(hdc, WINSIZE_X - 310, 30);
	miniMap->Render(hdc, WINSIZE_X / 2 - 130, 10);
}

void BattleScene::CheckUi()	//BattleScene 버튼 상호작용
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&(unit_Frame[0].frameBox), g_ptMouse))
		{
			unit_Frame[0].canPurchase = false;
			playerMgr->Init(unit_Frame[0].selectNum, collisionChecker);
		}
		if (PtInRect((&attackBox), g_ptMouse) && attackStatus == ATTACKSTATUS::READY)
		{
			attackStatus = ATTACKSTATUS::FIRED;
			currFrameX = 0;
		}
	}
}

void BattleScene::EnemyInit() //Enemy Init 작동방식 구현
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
	{
		enemyMgr->Init(1, collisionChecker);
	}
}

void BattleScene::ApCount()	//AP시스템 관련(적 AP증가값 포함)
{
	playerApTimer += TimerManager::GetSingleton()->GetElapsedTime();
	enemyApTimer += TimerManager::GetSingleton()->GetElapsedTime();
	if (playerApTimer >= apChargeTime[playerApLevel])
	{
		playerApTimer = 0.0f;
		playerAP++;
		if (playerAP >= maxAp[playerApLevel])
		{
			playerAP = maxAp[playerApLevel];
		}
	}
	if (enemyApTimer >= apChargeTime[enemyApLevel])
	{
		enemyApTimer = 0;
		enemyAP++;
		if (enemyAP >= maxAp[enemyApLevel])
		{
			enemyAP = maxAp[enemyApLevel];
		}
	}
}
