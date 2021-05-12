#pragma once
#include "CharacterData.h"
#include <list>
class CharacterData;
class CollisionChecker
{
private:
	list<CharacterData*>  lPlayerCharacter;
	list<CharacterData*>::iterator itlPlayerCharacter;
	list<CharacterData*> lEnemyCharacter;
	list<CharacterData*> itlEnemyCharacter;
public:
	void Release();
	void AddPlayerCharacter(CharacterData* characterData) { lPlayerCharacter.push_back(characterData); }
	void EraseDeadPlayerCharacter(CharacterData* characterData) { lPlayerCharacter.remove(characterData); }

	void AddEnemyCharacter(CharacterData* characterData) { lEnemyCharacter.push_back(characterData); }
	void EraseDeadEnemyCharacter(CharacterData* characterData) { lEnemyCharacter.remove(characterData); }
};

