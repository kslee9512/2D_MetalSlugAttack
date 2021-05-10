#pragma once
#include "GameNode.h"
class Image;
class CollisionChecker;
class PlayerManager;
typedef struct FrameUi
{
	Image* unit_Frame_able;
	Image* unit_Frame_unable;
	bool canPurchase;
	RECT frameBox;
};
enum class ATTACKSTATUS {UNDO, READY, FIRED};

class BattleScene : public GameNode
{
private:
	Image* backGround;
	Image* ui_Up;
	Image* ui_Down;
	Image* attack_Undo;
	Image* attack_Ready;
	Image* attack_Fire;
	FrameUi unit_Frame[5];
	CollisionChecker* collisionChecker;
	RECT attackBox;
	PlayerManager* playerMgr;
	int attackUndoFrame;
	int attackReadyFrame;
	int attackFireFrame;
	float changeTime;
	float checkAttackCool;
	int currFrameX;
	ATTACKSTATUS attackStatus;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckPurchase();
	void CheckAttackButton();

	virtual ~BattleScene() {};
};

