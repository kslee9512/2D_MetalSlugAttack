#pragma once
#include "CharacterData.h"
#include <list>
class CharacterData;
class CollisionChecker
{
private:
	list<CharacterData*>  lPlayerCharacter;
	list<CharacterData*>::iterator itlPlayerCharacter;

public:
	void AddPlayerCharacter(CharacterData* characterData) { lPlayerCharacter.push_back(characterData); }
	void EraseDeadCharacter(CharacterData* characterData) { lPlayerCharacter.remove(characterData); }
};

