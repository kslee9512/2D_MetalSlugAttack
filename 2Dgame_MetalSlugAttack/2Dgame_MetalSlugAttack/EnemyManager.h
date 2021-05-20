#pragma once
#include "GameNode.h"
#include <vector>

class CollisionChecker;
class Enemy;
class EnemyManager : public GameNode
{
private:
	vector<Enemy*> vEnemyMgr;
	vector<Enemy*>::iterator itlEnemyMgr;
	CollisionChecker* collisionChecker;
public:
	HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);
	vector<Enemy*> GetEnemyVector() { return this->vEnemyMgr; }
};

