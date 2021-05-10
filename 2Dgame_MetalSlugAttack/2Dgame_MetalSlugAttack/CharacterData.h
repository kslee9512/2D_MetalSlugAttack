#pragma once
#include "GameNode.h"

enum class STATUS{STAND, WALK, FIRE, DEAD};
class CollisionChecker;
class CharacterData : public  GameNode
{
private:
	string Name;
	Image* image_Stand;
	Image* image_Walk;
	Image* image_Fire;
	Image* image_Dead;
	FPOINT pos;
	bool isAlive;
	int currFrameX;
	UnitType unitType;
	RECT attackRange;
	RECT hitBox;
	STATUS characterStatus;
	float attackCooltime;
	float purchaseCooltime;
	float changeTimer;
	float moveSpeed;
	CollisionChecker* collisionChecker;
public:
	 HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	 void Release();
	 void Update();
	 void Render(HDC hdc);
	 void SetCollisionList();
};

