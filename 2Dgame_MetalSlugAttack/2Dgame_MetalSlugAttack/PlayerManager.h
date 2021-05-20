#pragma once
#include "GameNode.h"
#include <vector>

class CollisionChecker;
class Player;
class PlayerManager : public GameNode
{
private:
	vector<Player*> vPlayerCharacter;
	vector<Player*>::iterator itlPlayerCharacter;
	CollisionChecker* collisionChecker;
public:
	 HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	 void Release();
	 void Update();
	 void Render(HDC hdc);
	 vector<Player*> GetPlayerVector() { return this->vPlayerCharacter; }
};