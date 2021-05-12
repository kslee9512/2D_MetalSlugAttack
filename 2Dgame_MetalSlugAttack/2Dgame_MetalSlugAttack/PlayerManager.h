#pragma once
#include "GameNode.h"
#include <vector>

class CollisionChecker;
class CharacterData;
class PlayerManager : public GameNode
{
private:
	vector<CharacterData*> vPlayerCharacter;
	vector<CharacterData*>::iterator itlPlayerCharacter;
	CollisionChecker* collisionChecker;
public:
	 HRESULT Init(int unitNum, CollisionChecker* collisionChecker);
	 void Release();
	 void Update();
	 void Render(HDC hdc);
	 vector<CharacterData*> GetPlayerVector() { return this->vPlayerCharacter; }
};