#pragma once
#include "GameNode.h"
class Image;
class CollisionChecker;
typedef struct FrameUi
{
	Image* unit_Frame_able;
	Image* unit_Frame_unable;
	bool canPurchase;
	RECT frameBox;
};

class BattleScene : public GameNode
{
private:
	Image* backGround;
	Image* ui_Up;
	Image* ui_Down;
	FrameUi unit_Frame[5];
	CollisionChecker* collisionChecker;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckPurchase();

	virtual ~BattleScene() {};
};

