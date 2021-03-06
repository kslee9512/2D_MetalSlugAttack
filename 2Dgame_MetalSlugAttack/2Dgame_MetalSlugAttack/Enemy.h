#pragma once
#include "GameNode.h"

class Player;
class PlayerManager;
class CollisionChecker;
class Enemy : public GameNode
{
private:
	CollisionChecker* collisionChecker;
	Player* target;
	PlayerManager* playerBase;
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
	bool findBase;
	bool endDeadScene;
	bool isKnockback;
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
	int knockbackCount;
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
	void KnockBackUpdate();

	void SetStatus(STATUS status) { this->characterStatus = status; }
	void SetFindEnemy(bool findEnemy) { this->findEnemy = findEnemy; }
	void SetCurrFrameX(int currFrameX) { this->currFrameX = currFrameX; }
	void SetReadyToFire(bool readyToFire) { this->readyToFire = readyToFire; }
	void SetCharacterHp(int damage) { this->characterHp -= damage; }
	void SetCharacterHp0() { this->characterHp = 0; }
	void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	void SetTarget(Player* enemy) { this->target = enemy; }
	void SetTarget(PlayerManager* playerBase) { this->playerBase = playerBase; }
	void SetFindBase(bool findBase) { this->findBase = findBase; }

	void PlusCurrAttackCount() { this->currAttackCount++; }
	void SetCurrAttackCount(int count) { this->currAttackCount = count; }
	int GetCurrAttackCount() { return this->currAttackCount; }
	int GetCharacterAtk() { return this->characterAtk; }
	int GetCharacterHp() { return this->characterHp; }
	int GetMaxAttackCount() { return this->maxAttackCount; }
	bool GetFindEnemy() { return this->findEnemy; }
	bool GetReadyToFire() { return this->readyToFire; }
	bool GetCharacterAlive() { return this->isAlive; }
	bool GetEndDeadScene() { return this->endDeadScene; }
	void SetKnockBack(bool isKnockback) { this->isKnockback = isKnockback; }
	RECT GetAttackBox() { return this->attackRange; }
	RECT GetHitBox() { return this->hitBox; }
	STATUS GetStatus() { return this->characterStatus; }
	FPOINT GetHitPos() { return this->hitBoxPos; }
	Player* GetTarget() { return this->target; }
};

