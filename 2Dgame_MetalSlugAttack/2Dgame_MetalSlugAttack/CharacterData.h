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
	bool findEnemy;
	int currFrameX;
	UnitType unitType;
	RECT attackRange;
	RECT hitBox;
	STATUS characterStatus;
	float attackCooltime;
	float purchaseCooltime;
	float changeTimer;
	float moveSpeed;
	float fireCount;
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
	 void CheckFireCount();

	 void SetStatus(STATUS status) { this->characterStatus = status; }
	 void SetFindEnemy(bool findEnemy) { this->findEnemy = findEnemy; }
	 void SetCurrFrameX(int currFrameX) { this->currFrameX = currFrameX; }
	 void SetReadyToFire(bool readyToFire) { this->readyToFire = readyToFire; }
	 void SetCharacterHp(int damage) { this->characterHp -= damage; }
	 int GetCharacterAtk() { return this->characterAtk; }
	 int GetCharacterHp() { return this->characterHp; }
	 bool GetFindEnemy() { return this->findEnemy; }
	 bool GetReadyToFire() { return this->readyToFire; }
	 bool GetCharacterAlive() { return this->isAlive; }
	 RECT GetAttackBox() { return this->attackRange; }
	 RECT GetHitBox() { return this->hitBox; }
	 STATUS GetStatus() { return this->characterStatus; }
};