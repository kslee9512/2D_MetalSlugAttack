#pragma once
#include "GameNode.h"
typedef struct FrameUi
{
	Image* unit_Frame_able;
	Image* unit_Frame_unable;
	bool canPurchase;
	RECT frameBox;
	int selectNum;
	int unitCoast;
};
class ApManager : public GameNode
{
private:
	float playerApTimer;
	float enemyApTimer;
	float apImageCount;
	int apCurrFrameX;
	int apWalkFrame;
	int apPurchaseFrame;
	int playerAP;
	int enemyAP;
	float apChargeTime[5];
	int maxAp[5];
	int playerApLevel;
	int enemyApLevel;
	int apLvUpCoast[4];
	FrameUi apFrame;
public:
	void ApCount();
};