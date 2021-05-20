#pragma once
#include "GameNode.h"
class Image;
class CollisionChecker;
class PlayerManager;
class EnemyManager;
typedef struct FrameUi
{
	Image* unit_Frame_able;
	Image* unit_Frame_unable;
	bool canPurchase;
	RECT frameBox;
	int selectNum;
	int unitCoast;
};
enum class ATTACKSTATUS {UNDO, READY, FIRED};

class BattleScene : public GameNode
{
private:
	//UI
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
	FrameUi unit_Frame[5];
	ATTACKSTATUS attackStatus;
	int currFrameX;
	RECT attackBox;
	int attackUndoFrame;
	int attackReadyFrame;
	int attackFireFrame;
	float changeTime;
	float checkAttackCool;
	float attackCool;
	int playerAP;
	int enemyAP;
	int maxApLevel;
	int maxAp[5];
	float apChargeTime[5];
	float playerApTimer;
	float enemyApTimer;
	int playerApLevel;
	int enemyApLevel;

	CollisionChecker* collisionChecker;	//충돌처리
	PlayerManager* playerMgr;
	EnemyManager* enemyMgr;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	
	void CheckUi();
	void EnemyInit();
	void ApCount();
	virtual ~BattleScene() {};
};

