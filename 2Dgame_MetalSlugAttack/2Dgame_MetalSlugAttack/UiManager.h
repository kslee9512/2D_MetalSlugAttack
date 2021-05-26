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
	Image* coolTimeBar;
	bool canPurchase;
	bool endCoolTime;
	RECT frameBox;
	FPOINT portraitPos;
	int selectNum;
	int unitCoast;
	int calcUnitCoast[3];
	int currCoolTime;
	int purchaseCoolTime;
	float checkCoolTime;
};
typedef struct enemyAp
{
	int enemyApLevel;
	int enemyAP;
	float enemyApTimer;
	int unitCoast[3];
	int unitNum;
	float coolTime[3];
	int enemyUnitCoolTime[3];
	bool canPurchase[3];
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
	float apImageCount;
	int apCurrFrameX;
	int apWalkFrame;
	int apPurchaseFrame;
	int playerAP;
	int currAp_calcNum[5];
	int maxAp_calcNum[5];
	float apChargeTime[5];
	int maxAp[5];
	int playerApLevel;
	int apLvUpCoast[5];
	int maxApLevel;
	FrameUi apFrame;
	FrameUi unitFrame[5];
	APSTATUS apStatus;
	enemyAp enemyAp;
public:
	HRESULT Init();
	void Update();
	void ApCount();
	void Render(HDC hdc);
	void UpdateNumImage();
	void PurchaseAp();
	bool CheckEnemyAP();
	void RunEnemyCool();
	int PurchaseUnit();
	bool CheckUnitPurchase();
	int GetEnemyUnitNum() { return this->enemyAp.unitNum; }
};