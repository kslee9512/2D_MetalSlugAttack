#pragma once
#include "GameNode.h"

enum class STATUS{STAND, WALK, FIRE, DEAD, WIN};
class CollisionChecker;
class CharacterData : public  GameNode
{
private:
	CollisionChecker* collisionChecker;
	string Name;
	Image* image_Stand;
	Image* image_Walk;
	Image* image_Fire;
	Image* image_Dead;
	Image* image_Win;
	FPOINT pos;
	FPOINT hitBoxPos;
	FPOINT attackBoxPos;
	bool isAlive;
	bool readyToFire;
	int currFrameX;
	UnitType unitType;
	RECT attackRange;
	RECT hitBox;
	STATUS characterStatus;
	float attackCooltime;
	float purchaseCooltime;
	float changeTimer;
	float moveSpeed;
	int standMaxFrame;
	int walkMaxFrame;
	int fireMaxFrame;
	int deadMaxFrame;
	int winMaxFrame;
	int characterHp;
	int characterAtk;
	int unitCoast;
	int hitBoxWidth;
	int hitBoxHeight;
	int attackRangeWidth;
	int attackRangeHeight;
	int maxAttackCount;
	int attackCount;
public:
	 HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	 void Release();
	 void Update();
	 void Render(HDC hdc);
	 void Move();

	 bool GetCharacterAlive() { return this->isAlive; }
	 RECT GetAttackBox() { return this->attackRange; }
	 RECT GetHitBox() { return this->hitBox; }
	 void AddCollisionList();
};

