#include "UiManager.h"
#include "Image.h"
HRESULT UiManager::Init()
{
	ImageManager::GetSingleton()->AddImage("currAp", "Image/Ui/ap_number.bmp", 100, 20, 10, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("maxAp", "Image/Ui/ap_number_null.bmp", 100, 20, 10, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("purchasenum", "Image/Ui/purchasenum.bmp", 200, 20, 10, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("nullpurchasenum", "Image/Ui/rednum.bmp", 200, 20, 10, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("aptext", "Image/Ui/ap.bmp", 80, 80, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("apseparate", "Image/Ui/ap_separate.bmp", 80, 80, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("apwalk", "Image/Ui/ap_walk.bmp", 600, 50, 12, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("appurchase", "Image/Ui/ap_purchase.bmp", 850, 50, 17, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("unit_frame", "Image/Ui/unit_Frame.bmp", 80, 80, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("unit_frame_undo", "Image/Ui/unit_Frame_undo.bmp", 80, 80, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("coastframe", "Image/Ui/PriceFrame.bmp", 90, 30, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("maxLv", "Image/Ui/maxlevel.bmp", 40, 20, true, RGB(255, 255, 255));
	maxApImage = ImageManager::GetSingleton()->FindImage("maxLv");
	for (int i = 0; i < 3; i++)
	{
		apFrame.coastImage_able[i] = ImageManager::GetSingleton()->FindImage("purchasenum");
		apFrame.coastImage_unable[i] = ImageManager::GetSingleton()->FindImage("nullpurchasenum");

	}
	apFrame.coastFrame = ImageManager::GetSingleton()->FindImage("coastframe");
	apFrame.unit_Frame_able = ImageManager::GetSingleton()->FindImage("unit_frame");
	apFrame.unit_Frame_unable = ImageManager::GetSingleton()->FindImage("unit_frame_undo");
	apFrame.canPurchase = false;
	ap_Walk = ImageManager::GetSingleton()->FindImage("apwalk");
	ap_Purchase = ImageManager::GetSingleton()->FindImage("appurchase");
	apText = ImageManager::GetSingleton()->FindImage("aptext");
	ap_Separate = ImageManager::GetSingleton()->FindImage("apseparate");
	currAp_1 = ImageManager::GetSingleton()->FindImage("currAp");
	currAp_10 = ImageManager::GetSingleton()->FindImage("currAp");
	currAp_100 = ImageManager::GetSingleton()->FindImage("currAp");
	currAp_1000 = ImageManager::GetSingleton()->FindImage("currAp");
	maxAp_1 = ImageManager::GetSingleton()->FindImage("maxAp");
	maxAp_10 = ImageManager::GetSingleton()->FindImage("maxAp");
	maxAp_100 = ImageManager::GetSingleton()->FindImage("maxAp");
	maxAp_1000 = ImageManager::GetSingleton()->FindImage("maxAp");
	maxApLevel = 4;
	apCurrFrameX = 0;
	playerApTimer = 0.0f;
	enemyApTimer = 0.0f;
	playerApLevel = 0;
	enemyApLevel = 0;
	playerAP = 0;
	enemyAP = 0;
	float timer = 0.07f;
	for (int i = 0; i < 5; i++)
	{
		apChargeTime[i] = timer;
		timer -= 0.01f;
	}
	int maxInt = 3000;
	for (int i = 0; i < 5; i++)
	{
		maxAp[i] = maxInt;
		maxInt += 1500;
	}
	int calcAp = maxAp[0];
	int calcNum = 0;
	for (int i = 0; i < 5; i++)
	{
		calcNum = calcAp % 10;
		maxAp_calcNum[i] = calcNum;
		calcAp /= 10;
	}
	for (int i = 0; i < 5; i++)
	{
		apLvUpCoast[i] = 80 * (i + 1);
	}
	calcAp = apLvUpCoast[0];
	calcNum = 0;
	for (int i = 0; i < 3; i++)
	{
		calcNum = calcAp % 10;
		calcApNum[i] = calcNum;
		calcAp /= 10;
	}
	apFrame.frameBox = { 60, 485, 140, 565 };
	endPurchase = true;
	apImageCount = 0.0f;
	apStatus = APSTATUS::NORMAL;
	return S_OK;
}

void UiManager::Update()
{
	ApCount();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		PurchaseAp();
	}
	UpdateNumImage();

}

void UiManager::ApCount()
{
	playerApTimer += TimerManager::GetSingleton()->GetElapsedTime();
	enemyApTimer += TimerManager::GetSingleton()->GetElapsedTime();
	apImageCount += TimerManager::GetSingleton()->GetElapsedTime();
	if (apImageCount >= 0.1f)
	{
		apImageCount = 0.0f;
		apCurrFrameX++;
		if (apStatus == APSTATUS::NORMAL && apCurrFrameX > 11)
		{
			apCurrFrameX = 0;
		}
		else if (apStatus == APSTATUS::PURCHASE && apCurrFrameX > 16)
		{
			if (playerApLevel == maxApLevel)
			{
				apCurrFrameX--;
			}
			else
			{ 
				apCurrFrameX = 0;
				apStatus = APSTATUS::NORMAL;
				endPurchase = true;
			}
		}
	}
	if (playerAP >= apLvUpCoast[playerApLevel] && endPurchase)
	{
		apFrame.canPurchase = true;
	}
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

void UiManager::Render(HDC hdc)
{
	apText->Render(hdc, 60, 445, true);
	ap_Separate->Render(hdc, 120, 445, true);
	currAp_1->FrameRender(hdc, 110, 445, currAp_calcNum[0], 0, true);
	currAp_10->FrameRender(hdc, 100, 445, currAp_calcNum[1], 0, true);
	currAp_100->FrameRender(hdc, 90, 445, currAp_calcNum[2], 0, true);
	currAp_1000->FrameRender(hdc, 80, 445, currAp_calcNum[3], 0, true);
	maxAp_1000->FrameRender(hdc, 130, 445, maxAp_calcNum[3], 0, true);
	maxAp_100->FrameRender(hdc, 140, 445, maxAp_calcNum[2], 0, true);
	maxAp_10->FrameRender(hdc, 150, 445, maxAp_calcNum[1], 0, true);
	maxAp_1->FrameRender(hdc, 160, 445, maxAp_calcNum[0], 0, true);
	if (apFrame.canPurchase)
	{
		apFrame.unit_Frame_able->Render(hdc, 100, 525, true);
		apFrame.coastFrame->Render(hdc, 100, 565, true);
		if (playerApLevel != maxApLevel)
		{
			apFrame.coastImage_able[0]->FrameRender(hdc, 110, 565, calcApNum[0], 0, true, 2);
			apFrame.coastImage_able[1]->FrameRender(hdc, 100, 565, calcApNum[1], 0, true, 2);
			apFrame.coastImage_able[2]->FrameRender(hdc, 90, 565, calcApNum[2], 0, true, 2);
		}
		if (playerApLevel == maxApLevel)
		{
			maxApImage->Render(hdc, 100, 565, true);
		}

	}
	else if (!(apFrame.canPurchase))
	{
		apFrame.unit_Frame_unable->Render(hdc, 100, 525, true);
		apFrame.coastFrame->Render(hdc, 100, 565, true);
		apFrame.coastImage_unable[0]->FrameRender(hdc, 110, 565, calcApNum[0], 0, true, 2);
		apFrame.coastImage_unable[1]->FrameRender(hdc, 100, 565, calcApNum[1], 0, true, 2);
		apFrame.coastImage_unable[2]->FrameRender(hdc, 90, 565, calcApNum[2], 0, true, 2);
	}
	if (endPurchase)
	{
		ap_Walk->FrameRender(hdc, 100, 525, apCurrFrameX, 0, true);
	}
	else if (!endPurchase)
	{
		ap_Purchase->FrameRender(hdc, 100, 525, apCurrFrameX, 0, true);
	}

	wsprintf(test, "%d , %d", playerAP, playerApLevel);
	TextOut(hdc, 80, 400, test, strlen(test));
}

void UiManager::UpdateNumImage()
{
	int calcAp = playerAP;
	int printNum;
	for (int i = 0; i < 4; i++)
	{
		printNum = calcAp % 10;
		currAp_calcNum[i] = printNum;
		calcAp /= 10;
	}
}

void UiManager::PurchaseAp()
{
	if (apFrame.canPurchase && PtInRect(&(apFrame.frameBox), g_ptMouse) && playerApLevel != maxApLevel)
	{
		playerAP -= apLvUpCoast[playerApLevel];
		playerApLevel++;
		if (playerApLevel > maxApLevel)
		{
			playerApLevel = maxApLevel;
		}
		apFrame.canPurchase = false;
		int calcAp = maxAp[playerApLevel];
		int calcNum = 0;
		for (int i = 0; i < 4; i++)
		{
			calcNum = calcAp % 10;
			maxAp_calcNum[i] = calcNum;
			calcAp /= 10;
		}
		calcAp = apLvUpCoast[playerApLevel];
		calcNum = 0;
		for (int i = 0; i < 3; i++)
		{
			calcNum = calcAp % 10;
			calcApNum[i] = calcNum;
			calcAp /= 10;
		}
		if (playerApLevel == maxApLevel)
		{
			apFrame.canPurchase = true;
		}
		endPurchase = false;
		apStatus = APSTATUS::PURCHASE;
		apCurrFrameX = 0;
	}
}
