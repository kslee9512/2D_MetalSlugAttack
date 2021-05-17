#pragma once
#include "CharacterData.h"
#include <list>
class CharacterData;
class PlayerManager;
class EnemyManager;
class CollisionChecker
{
private:
	list<CharacterData*>  lPlayerCharacter;
	list<CharacterData*>::iterator itlPlayerCharacter;
	list<CharacterData*> lEnemyCharacter;
	list<CharacterData*>::iterator itlEnemyCharacter;
public:
	void AddPlayerCharacter(CharacterData* characterData) { lPlayerCharacter.push_back(characterData); }
	void EraseDeadPlayerCharacter(CharacterData* characterData) { lPlayerCharacter.remove(characterData); }

	void AddEnemyCharacter(CharacterData* characterData) { lEnemyCharacter.push_back(characterData); }
	void EraseDeadEnemyCharacter(CharacterData* characterData) { lEnemyCharacter.remove(characterData); }

	void CheckAlive();
	void CheckAttackRange();
	void CalcDamage();
};