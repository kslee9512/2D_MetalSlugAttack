#pragma once
#include "GameNode.h"
#include <vector>

class CollisionChecker;
class Player;
class PlayerManager : public GameNode
{
private:
	Image* playerBase;
	RECT playerBaseHitBox;
	int baseHp;
	int baseEngageFrame;
	int currFrameX;
	float frameTimer;
	bool isStart;

	vector<Player*> vPlayerCharacter;
	vector<Player*>::iterator itlPlayerCharacter;
	CollisionChecker* collisionChecker;
public:
	 HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	 HRESULT BaseInit();
	 void Release();
	 void Update();
	 void Render(HDC hdc);
	 void SetBaseHp(int damage) { this->baseHp -= damage; }
	 int GetPlayerBaseHp() { return this->baseHp; }
	 RECT GetPlayerBaseHitBox() { return this->playerBaseHitBox; }
	 vector<Player*> GetPlayerVector() { return this->vPlayerCharacter; }
};