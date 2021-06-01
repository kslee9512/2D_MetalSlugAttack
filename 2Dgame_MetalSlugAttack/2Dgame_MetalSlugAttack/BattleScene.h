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
	Image* text_Mission;
	Image* text_Start;
	Image* text_Complete;
	Image* failed_Mission;
	Image* text_Failed;
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
	float startTimer;
	float failedTimer;
	float winTimer;
	int textMoveTimer;
	int textPosition[2];
	int playerApLevel;
	int enemyApLevel;
	bool isEndGame;
	bool isReadyGame;
	bool isPlayerDefeat;
	bool isPlayerWin;
	CollisionChecker* collisionChecker;	//충돌처리4
	UiManager* uiMgr;
	PlayerManager* playerMgr;
	EnemyManager* enemyMgr;
public:
	virtual HRESULT Init(int* unitNum);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	
	void EnemyInit();
	void StartTextMove();
	void EndTextMove();
	virtual ~BattleScene() {};
};

