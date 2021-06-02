#pragma once
#include "GameNode.h"
#include <vector>

class CollisionChecker;
class Enemy;
class EnemyManager : public GameNode
{
private:
	Image* enemyBase;
	RECT enemyBaseHitBox;
	int baseHp;
	int baseEngageFrame;
	int currFrameX;
	float frameTimer;
	bool isStart;
	bool isDefeat;
	vector<Enemy*> vEnemyMgr;
	vector<Enemy*>::iterator itlEnemyMgr;
	CollisionChecker* collisionChecker;
public:
	HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	HRESULT BaseInit();
	void Release();
	void Update();
	void Render(HDC hdc);
	void BaseRetreat();
	void SetBaseHp(int damage) { this->baseHp -= damage; }
	int GetEnemyBaseHp() { return this->baseHp; }
	RECT GetEnemyBaseHitBox() { return this->enemyBaseHitBox; }
	vector<Enemy*> GetEnemyVector() { return this->vEnemyMgr; }
	void SetIsDefeat(bool isDefeat) { this->isDefeat = isDefeat; }
};

