#include "BattleScene.h"
#include "Image.h"
#include "CollisionChecker.h"
#include "PlayerManager.h"
HRESULT BattleScene::Init()
{
	ImageManager::GetSingleton()->AddImage("background", "Image/Background/background.bmp", WINSIZE_X, 380);
	ImageManager::GetSingleton()->AddImage("ui_up", "Image/Ui/Ui_Up.bmp", WINSIZE_X, 70);
	ImageManager::GetSingleton()->AddImage("ui_down", "Image/Ui/Ui_Down.bmp", WINSIZE_X, 150);
	ImageManager::GetSingleton()->AddImage("unit_frame", "Image/Ui/unit_Frame.bmp", 80, 80);
	ImageManager::GetSingleton()->AddImage("unit_frame_undo", "Image/Ui/unit_Frame_undo.bmp", 80, 80);
	ImageManager::GetSingleton()->AddImage("Eri_walk", "Image/Eri/Eri_walk.bmp", 350, 50, 7, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Eri_stand", "Image/Eri/Eri_stand.bmp", 250, 50, 5, 1, true, RGB(255, 255, 255));
	unit_Frame[0].canPurchase = true;
	backGround = ImageManager::GetSingleton()->FindImage("background");
	if (backGround == nullptr)
	{
		MessageBox(g_hWnd, "battleScene_background_loadImage_fail", "image_Load_Fail", MB_OK);
		return E_FAIL;
	}
	ui_Up = ImageManager::GetSingleton()->FindImage("ui_up");
	if (ui_Up == nullptr)
	{
		MessageBox(g_hWnd, "battleScene_ui_Up_loadImage_fail", "image_Load_Fail", MB_OK);
		return E_FAIL;
	}
	ui_Down = ImageManager::GetSingleton()->FindImage("ui_down");
	if (ui_Down == nullptr)
	{
		MessageBox(g_hWnd, "battleScene_ui_Down_loadImage_fail", "image_Load_Fail", MB_OK);
		return E_FAIL;
	}
	unit_Frame[0].unit_Frame_able = ImageManager::GetSingleton()->FindImage("unit_frame");
	if (unit_Frame[0].unit_Frame_able == nullptr)
	{
		MessageBox(g_hWnd, "battleScene_unit_Frame_loadImage_fail", "image_Load_Fail", MB_OK);
		return E_FAIL;
	}
	unit_Frame[0].unit_Frame_unable = ImageManager::GetSingleton()->FindImage("unit_frame_undo");
	if(unit_Frame[0].unit_Frame_unable == nullptr)
	{
		MessageBox(g_hWnd, "battleScene_unit_Frame_undo_loadImage_fail", "image_Load_Fail", MB_OK);
		return E_FAIL;
	}
	unit_Frame[0].frameBox = { 250, 450, 330, 530 };
	collisionChecker = new CollisionChecker();
	playerMgr = new PlayerManager();

	return S_OK;
}

void BattleScene::Release()
{
	
}

void BattleScene::Update()
{
	CheckPurchase();
	playerMgr->Update();
	//ChangeFrameImage();
}

void BattleScene::Render(HDC hdc)
{
	backGround->Render(hdc, 0, 70);
	ui_Up->Render(hdc);
	ui_Down->Render(hdc, 0, 450);
	if (unit_Frame[0].canPurchase == true)
	{
		unit_Frame[0].unit_Frame_able->Render(hdc, 250, 480);
	}
	else if (unit_Frame[0].canPurchase == false)
	{
		unit_Frame[0].unit_Frame_unable->Render(hdc, 250, 480);
	}
	if (playerMgr->GetPlayerVector().size() >= 1)
	{
		playerMgr->Render(hdc);
	}
}

void BattleScene::CheckPurchase()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&(unit_Frame[0].frameBox), g_ptMouse))
		{
			unit_Frame[0].canPurchase = false;
			playerMgr->Init(1, collisionChecker);
		}
	}
}
