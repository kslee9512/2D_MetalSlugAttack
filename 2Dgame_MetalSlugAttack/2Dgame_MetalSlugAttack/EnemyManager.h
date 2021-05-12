#pragma once
#include "GameNode.h"
#include <vector>

class CollisionChecker;
class CharacterData;
class EnemyManager : public GameNode
{
private:
	vector<CharacterData*> vEnemyMgr;
	vector<CharacterData*>::iterator itlEnemyMgr;
	CollisionChecker* collisionChecker;
public:
	HRESULT Init(CollisionChecker* collisionChecker);
	void Release();
	void Update();
	void Render(HDC hdc);
	vector<CharacterData*> GetEnemyVector() { return this->vEnemyMgr; }
};

