#pragma once
#include "GameNode.h"
#include <list>

class Enemy;
class EnemyManager;
class CollisionChecker;
class Player : public GameNode
{
	CollisionChecker* collisionChecker;
	Enemy* target;
	list<Enemy*> ltarget;
	EnemyManager* enemyBase;
	string Name;
	Image* image_Stand;
	Image* image_Walk;
	Image* image_Fire;
	Image* image_Dead;
	Image* image_Win;
	FPOINT pos;
	FPOINT hitBoxPos;
	FPOINT attackBoxPos;
	AttackType attackType;
	bool needTarget;
	bool isAlive;
	bool readyToFire;
	bool findEnemy;
	bool findBase;
	bool endDeadScene;
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
	float characterAtk;
	int unitCoast;
	int hitBoxWidth;
	int hitBoxHeight;
	int attackRangeWidth;
	int attackRangeHeight;
	int maxAttackCount;
	int currAttackCount;

public:
	HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);
	void UpdateMove();
	void UpdateStand();
	void UpdateFire();
	void UpdateDead();
	void UpdateWin();

	void SetStatus(STATUS status) { this->characterStatus = status; }
	void SetFindEnemy(bool findEnemy) { this->findEnemy = findEnemy; }
	void SetCurrFrameX(int currFrameX) { this->currFrameX = currFrameX; }
	void SetReadyToFire(bool readyToFire) { this->readyToFire = readyToFire; }
	void SetCharacterHp(int damage) { this->characterHp -= damage; }
	void SetCharacterHp0() { this->characterHp = 0; }
	void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	void SetTarget(Enemy* enemy) { this->target = enemy; }
	void SetTarget(EnemyManager* enemyBase) { this->enemyBase = enemyBase; }
	void SetMultyTarget(Enemy* enemy) { this->ltarget.push_back(enemy); }
	void SetFindBase(bool findBase) { this->findBase = findBase; }
	void PlusCurrAttackCount() { this->currAttackCount++; }
	void SetCurrAttackCount() { this->currAttackCount += 1; }
	int GetCurrAttackCount() { return this->currAttackCount; }
	int GetCharacterAtk() { return this->characterAtk; }
	int GetCharacterHp() { return this->characterHp; }
	int GetMaxAttackCount() { return this->maxAttackCount; }
	bool GetEndDeadScene() { return this->endDeadScene; }
	bool GetFindEnemy() { return this->findEnemy; }
	bool GetReadyToFire() { return this->readyToFire; }
	bool GetCharacterAlive() { return this->isAlive; }
	RECT GetAttackBox() { return this->attackRange; }
	RECT GetHitBox() { return this->hitBox; }
	STATUS GetStatus() { return this->characterStatus; }
	AttackType GetAttackType() { return this->attackType; }
	void SetNeedTarget(bool needTarget) { this->needTarget = needTarget; }
	bool GetNeedTarget() { return this->needTarget; }
	int GetTargetList() { return this->ltarget.size(); }
};

