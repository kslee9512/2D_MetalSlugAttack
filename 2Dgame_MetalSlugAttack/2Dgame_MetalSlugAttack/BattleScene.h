#pragma once
#include "GameNode.h"
class Image;
class CollisionChecker;
class PlayerManager;
class EnemyManager;
class UiManager;

enum class ATTACKSTATUS {UNDO, READY, FIRED};

class BattleScene : public GameNode
{
private:
	//UI
	Image* apWalk;
	Image* apPurchase;
	Image* backGround;
	Image* ui_Up;
	Image* ui_Down;
	Image* attack_Undo;
	Image* attack_Ready;
	Image* attack_Fire;
	Image* hp_Frame[2];
	Image* miniMap;
	Image* pfText[2];
	Image* player_Hpbar;
	Image* enemy_Hpbar;
	Image* apBar;
	ATTACKSTATUS attackStatus;
	int currFrameX;
	int apCurrFrameX;
	RECT attackBox;
	int attackUndoFrame;
	int attackReadyFrame;
	int attackFireFrame;
	int apWalkFrame;
	int apPurchaseFrame;
	float changeTime;
	float checkAttackCool;
	float attackCool;
	float apImageCount;
	int playerAP;
	int enemyAP;
	int maxApLevel;
	int maxAp[5];
	float apChargeTime[5];
	float playerApTimer;
	float enemyApTimer;
	int playerApLevel;
	int enemyApLevel;

	CollisionChecker* collisionChecker;	//충돌처리4
	UiManager* uiMgr;
	PlayerManager* playerMgr;
	EnemyManager* enemyMgr;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	
	void EnemyInit();
	virtual ~BattleScene() {};
};

