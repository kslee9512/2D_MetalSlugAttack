#pragma once
#include "GameNode.h"
typedef struct FrameUi
{
	Image* unit_Frame_able;
	Image* unit_Frame_unable;
	Image* unit_Portrait_able;
	Image* unit_Portrait_Unable;
	Image* coastImage_able[3];
	Image* coastImage_unable[3];
	Image* coastFrame;
	bool canPurchase;
	RECT frameBox;
	int selectNum;
	int unitCoast;
	float purchaseCoolTime;
};
enum class APSTATUS { NORMAL, PURCHASE, MAX};
class UiManager : public GameNode
{
private:
	char test[128];
	bool endPurchase;
	Image* currAp_1;
	Image* currAp_10;
	Image* currAp_100;
	Image* currAp_1000;
	Image* maxAp_1;
	Image* maxAp_10;
	Image* maxAp_100;
	Image* maxAp_1000;
	Image* apText;
	Image* ap_Separate;
	Image* ap_Walk;
	Image* ap_Purchase;
	Image* maxApImage;
	int calcApNum[3];
	float playerApTimer;
	float enemyApTimer;
	float apImageCount;
	int apCurrFrameX;
	int apWalkFrame;
	int apPurchaseFrame;
	int playerAP;
	int currAp_calcNum[5];
	int maxAp_calcNum[5];
	int enemyAP;
	float apChargeTime[5];
	int maxAp[5];
	int playerApLevel;
	int enemyApLevel;
	int apLvUpCoast[5];
	int maxApLevel;
	FrameUi apFrame;
	FrameUi unitFrame;
	APSTATUS apStatus;
public:
	HRESULT Init();
	void Update();
	void ApCount();
	void Render(HDC hdc);
	void UpdateNumImage();
	void PurchaseAp();
};